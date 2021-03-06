/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 1998-2004 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission is hereby granted to licensees of Texas Instruments           |**
**| Incorporated (TI) products to use this computer program for the sole     |**
**| purpose of implementing a licensee product based on TI products.         |**
**| No other rights to reproduce, use, or disseminate this computer          |**
**| program, whether in part or in whole, are granted.                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

/** \file   pal_os.h
    \brief  OS Abstraction Header File

    This file provides visibility to OS abstraction APIs by including
    only the configured service modules interface files.

    (C) Copyright 2004, Texas Instruments, Inc

    \author     PSP Architecture Team
    \version    1.0
 */

#ifndef __PAL_OS_H__
#define __PAL_OS_H__

#include "pal_osCfg.h"


/* Added:
 * PAL OS module type to be placed in section D of the final "ERROR CODE"
 * as described in pal_defs.h
 */
#define PAL_OS_COMMON_ERR   (0)
#define PAL_OSMEM_ERR       (1)
#define PAL_OSBUF_ERR       (2)
#define PAL_OSSEM_ERR       (3)
#define PAL_OSMUTEX_ERR     (4)
#define PAL_OSWAIT_ERR      (5)
#define PAL_OSLIST_ERR      (6)
#define PAL_OSPROTECT_ERR   (7)

/* Common error codes for ALL PAL OS modules */
#define PAL_OS_COMMON_ERROR_CREATE(x)   (PAL_ERROR(PAL_CRITICAL_ERROR, PAL_OS_COMMON_ERR, 0, (x)))

/* Invalid parameter passed to the function error */
#define PAL_OS_ERROR_INVALID_PARAM      (PAL_OS_COMMON_ERROR_CREATE(1))

/* Feature not supported error */
#define PAL_OS_ERROR_NOT_SUPPORTED      (PAL_OS_COMMON_ERROR_CREATE(2))

/* No resources available error */
#define PAL_OS_ERROR_NO_RESOURCES       (PAL_OS_COMMON_ERROR_CREATE(3))

/* OS specific error */
#define PAL_OS_ERROR_OS_SPECIFIC        (PAL_OS_COMMON_ERROR_CREATE(4))


/* Default (memory) segment Id - Many of the modules (like OSSEM, OSBUF), 
 * depend upon a segment id to be passed in the API's. The macro below 
 * defines a default segment Id that can be used in these API's
 */
#define PAL_OSMEM_DEFAULT_SEGID         0


#ifdef INLINE
#define PAL_INLINE static inline
#else
#define PAL_INLINE
#endif

#ifdef PAL_INCLUDE_OSMEM
#include "pal_osMem.h"          /* OsMEM Services */
#endif /* PAL_INCLUDE_OSMEM */

#ifdef PAL_INCLUDE_OSBUF
#include "pal_osBuf.h"          /* OsBUF Services */
#endif /* PAL_INCLUDE_OSBUF */

#ifdef PAL_INCLUDE_OSSEM
#include "pal_osSem.h"          /* OsSEM Services */
#endif /* PAL_INCLUDE_OSSEM */

#ifdef PAL_INCLUDE_OSMUTEX
#include "pal_osMutex.h"        /* OsMUTEX Services */
#endif /* PAL_INCLUDE_OSMUTEX */

#ifdef PAL_INCLUDE_OSWAIT
#include "pal_osWait.h"        /* OsWAIT Services */
#endif /* PAL_INCLUDE_OSWAIT */

#ifdef PAL_INCLUDE_OSLIST
#include "pal_osList.h"         /* OsLIST Services */
#endif /* PAL_INCLUDE_OSLIST */

#ifdef PAL_INCLUDE_OSPROTECT
#include "pal_osProtect.h"      /* OsPROTECT Services */
#endif /* PAL_INCLUDE_OSPROTECT */

#ifdef PAL_INCLUDE_OSCACHE
#include "pal_osCache.h"      /* OsCACHE Services */
#endif /* PAL_INCLUDE_OSCACHE */

#ifdef INLINE

#ifdef PAL_INCLUDE_OSBUF
#include "pal_osBuf_inline.h"
#endif /* PAL_INCLUDE_OSBUF */

#ifdef PAL_INCLUDE_OSMEM
#include "pal_osMem_inline.h"
#endif /* PAL_INCLUDE_OSMEM */

#ifdef PAL_INCLUDE_OSMUTEX
#include "pal_osMutex_inline.h"
#endif /* PAL_INCLUDE_OSMUTEX */

#ifdef PAL_INCLUDE_OSSEM
#include "pal_osSem_inline.h"
#endif /* PAL_INCLUDE_OSSEM */

#ifdef PAL_INCLUDE_OSWAIT
#include "pal_osWait_inline.h"
#endif /* PAL_INCLUDE_OSWAIT */

#ifdef PAL_INCLUDE_OSPROTECT
#include "pal_osProtect_inline.h"
#endif /* PAL_INCLUDE_OSPROTECT */

#ifdef PAL_INCLUDE_OSLIST
#include "pal_osList_inline.h"
#endif /* PAL_INCLUDE_OSLIST */

#ifdef PAL_INCLUDE_OSCACHE
#include "pal_osCache_inline.h"      /* OsCACHE Services */
#endif /* PAL_INCLUDE_OSCACHE */

#endif /* INLINE */

#endif /* _PAL_OS_H_ */

