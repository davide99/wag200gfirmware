/* a quick port of my libmsock routine to MS NT */
/* muquit@Aug-20-2005  Mar 01  Eastern Standard Time 2001 */

#include "msock.h"

#ifdef HAVE_OPENSSL
static SSL      *s_ssl=NULL;
#endif /* HAVE_OPENSSL */

static SOCKET   s_sock;
static int      ssl_status=0;

void msock_set_socket(SOCKET sfd)
{
    s_sock=sfd;
}

SOCKET msock_get_socket(void)
{
    return(s_sock);
}

void msock_turn_ssl_on(void)
{
    ssl_status=1;
}
void msock_turn_ssl_off(void)
{
    ssl_status=0;
}
int msock_is_ssl_on(void)
{
    return(ssl_status);
}

#ifdef HAVE_OPENSSL
void msock_set_ssl(SSL *ssl)
{
    s_ssl=ssl;
}
SSL *msock_get_ssl(void)
{
    return(s_ssl);
}
#endif /* HAVE_OPENSSL */

struct in_addr *atoAddr(char *address)
{
    struct hostent
        *host;

    static struct in_addr
        saddr;

    saddr.s_addr=inet_addr(address);
    if (saddr.s_addr != -1)
        return (&saddr);

    host=gethostbyname(address);
    if (host != (struct hostent *) NULL)
        return ((struct in_addr *) *host->h_addr_list);

    return ((struct in_addr *) NULL);
}

#ifdef WINNT
/* returns 0 on success -1 on failure */
int initWinSock(void)
{
    WORD
        version_requested;

    WSADATA
        wsa_data;

    int
        err;

    version_requested=MAKEWORD(2,0);
    err=WSAStartup(version_requested,&wsa_data);
    if (err != 0)
    {
        (void) fprintf(stderr," Unable to initialize winsock (%d)\n",err);
        return(-1);
    }

    return(0);
}
#endif /* WINNT */

/* returns SOCKET on success INVALID_SOCKET on failure */
SOCKET clientSocket(char *address,int port)
{
    SOCKET
        s;

    struct sockaddr_in
        sa;

    struct in_addr
        *addr;

    int
        rc;

#ifdef WINNT
    rc=initWinSock();
    if (rc != 0)
        return(INVALID_SOCKET);
#endif /* WINNT */
    
    addr=atoAddr(address);
    if (addr == NULL)
    {
        (void) fprintf(stderr," Invalid address: %s\n",address);
        return(INVALID_SOCKET);
    }

    memset((char *) &sa,0,sizeof(sa));
    sa.sin_family=AF_INET;
    sa.sin_port=htons(port);
    sa.sin_addr.s_addr=addr->s_addr;

    /* open the socket */
    s=socket(AF_INET,SOCK_STREAM,PF_UNSPEC);
    if (s == INVALID_SOCKET)
    {
        (void) fprintf(stderr," Could not create socket\n");
        return(INVALID_SOCKET);
    }

    /* connect */
    rc=connect(s,(struct sockaddr *) &sa,sizeof(sa));
    if (rc < 0)
        return(INVALID_SOCKET);


    return(s);
}



/*
** this function writes a character string out to a socket.
** it returns -1 if the connection is closed while it is trying to
** write
*/
static int sockWrite(SOCKET sock,char *str,size_t count)
{
    size_t
        bytesSent=0;

    int
        thisWrite;

    while (bytesSent < count)
    {
       thisWrite=send(sock,str,count-bytesSent,0);
       /*
       (void) fprintf(stderr,"str=%s\n",str);
       (void) fprintf(stderr,"count=%d\n",count);
       */

       if (thisWrite <= 0)
          return (thisWrite);

        bytesSent += thisWrite;
        str += thisWrite;
    }
    return (count);
}

#ifdef HAVE_OPENSSL
int sockWriteSSL(SSL *ssl,char *str,size_t count)
{
    size_t
        bytesSent=0;

    int
        thisWrite;

    while (bytesSent < count)
    {
       thisWrite=SSL_write(ssl,str,count-bytesSent);
       if (thisWrite <= 0)
          return (thisWrite);

        bytesSent += thisWrite;
        str += thisWrite;
    }
    return (count);
}
int sockPutsSSL(SSL *ssl,char *str)
{
    return (sockWriteSSL(ssl,str,strlen(str)));
}
#endif /* HAVE_OPENSSL */

int sockPuts(SOCKET sock,char *str)
{
    return (sockWrite(sock,str,strlen(str)));
}

int sockGets(SOCKET sockfd,char *str,size_t count)
{
    int
        bytesRead;

    int
        totalCount=0;

    char
        buf[1],
        *currentPosition;

    char
        lastRead=0;

    currentPosition=str;

    while (lastRead != 10)
    {
        bytesRead=recv(sockfd,buf,1,0);
        if (bytesRead <= 0)
        {
            /*
            ** the other side may have closed unexpectedly
            */
            return (-1);
        }
        lastRead=buf[0];

        if ((totalCount < count) && (lastRead != 10)
            && (lastRead != 13))
        {
            *currentPosition=lastRead;
            currentPosition++;
            totalCount++;
        }
    }
    if (count > 0)
        *currentPosition=0;

    return (totalCount);
}
#ifdef HAVE_OPENSSL
int sockGetsSSL(SSL *ssl,char *str,size_t count)
{
    int
        bytesRead;

    int
        totalCount=0;

    char
        buf[1],
        *currentPosition;

    char
        lastRead=0;

    currentPosition=str;
    while (lastRead != 10)
    {
        bytesRead=SSL_read(ssl,buf,1);
        if (bytesRead <= 0)
        {
            /*
            ** the other side may have closed unexpectedly
            */
            return (-1);
        }
        lastRead=buf[0];

        if ((totalCount < count) && (lastRead != 10)
            && (lastRead != 13))
        {
            *currentPosition=lastRead;
            currentPosition++;
            totalCount++;
        }
    }
    if (count > 0)
        *currentPosition=0;

    return (totalCount);
}
#endif /* HAVE_OPENSSL */

/* must be called after msock_set_socket() */
/* must be called after msock_set_ssl() if SSL is on */
int msock_gets(char *str,size_t count)
{
    if (! msock_is_ssl_on())
    {
        return(sockGets(msock_get_socket(),str,count));
    }
    else
    {
#ifdef HAVE_OPENSSL
        return(sockGetsSSL(msock_get_ssl(),str,count));
#endif /* HAVE_OPENSSL */
    }
    return(-1);
}

/* must be called after msock_set_socket() */
/* must be called after msock_set_ssl() if SSL is on */
int msock_puts(char *str)
{
    if (! msock_is_ssl_on())
    {
        return(sockPuts(msock_get_socket(),str));
    }
    else
    {
#ifdef HAVE_OPENSSL
        return(sockPutsSSL(msock_get_ssl(),str));
#endif /* HAVE_OPENSSL */
    }
    return(-1);
}
void msock_close_socket(SOCKET fd)
{
#ifdef WINNT
    closesocket(fd);
#else
    close(fd);
#endif /* MSOCK_WIN32 */

}

void msock_close(void)
{
    msock_close_socket(msock_get_socket());
}

