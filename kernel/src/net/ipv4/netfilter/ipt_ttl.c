/* TTL modification target for IP tables
 * (C) 2000 by Harald Welte <laforge@gnumonks.org>
 *
 * Version: 1.2
 *
 * This software is distributed under the terms of GNU GPL
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/checksum.h>

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_TTL.h>

MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("IP tables TTL modification module");
MODULE_LICENSE("GPL");

static unsigned int ipt_ttl_target(struct sk_buff **pskb, unsigned int hooknum,
		const struct net_device *in, const struct net_device *out,
		const void *targinfo, void *userinfo)
{
	struct iphdr *iph = (*pskb)->nh.iph;
	const struct ipt_TTL_info *info = targinfo;
	u_int16_t diffs[2];
	int new_ttl;
			 
	switch (info->mode) {
		case IPT_TTL_SET:
			new_ttl = info->ttl;
			break;
		case IPT_TTL_INC:
			new_ttl = iph->ttl + info->ttl;
			if (new_ttl > 255)
				new_ttl = 255;
			break;
		case IPT_TTL_DEC:
			new_ttl = iph->ttl + info->ttl;
			if (new_ttl < 0)
				new_ttl = 0;
			break;
		default:
			new_ttl = iph->ttl;
			break;
	}

	if (new_ttl != iph->ttl) {
		diffs[0] = htons(((unsigned)iph->ttl) << 8) ^ 0xFFFF;
		iph->ttl = new_ttl;
		diffs[1] = htons(((unsigned)iph->ttl) << 8);
		iph->check = csum_fold(csum_partial((char *)diffs,
						    sizeof(diffs),
				 	            iph->check^0xFFFF));
									                	(*pskb)->nfcache |= NFC_ALTERED;
	}

	return IPT_CONTINUE;
}

static int ipt_ttl_checkentry(const char *tablename,
		const struct ipt_entry *e,
		void *targinfo,
		unsigned int targinfosize,
		unsigned int hook_mask)
{
	struct ipt_TTL_info *info = targinfo;

	if (targinfosize != IPT_ALIGN(sizeof(struct ipt_TTL_info))) {
		printk(KERN_WARNING "TTL: targinfosize %u != %Zu\n",
				targinfosize,
				IPT_ALIGN(sizeof(struct ipt_TTL_info)));
		return 0;	
	}	

	if (strcmp(tablename, "mangle")) {
		printk(KERN_WARNING "TTL: can only be called from \"mangle\" table, not \"%s\"\n", tablename);
		return 0;
	}

	if (info->mode > IPT_TTL_MAXMODE) {
		printk(KERN_WARNING "TTL: invalid or unknown Mode %u\n", 
			info->mode);
		return 0;
	}

	if ((info->mode != IPT_TTL_SET) && (info->ttl == 0)) {
		printk(KERN_WARNING "TTL: increment/decrement doesn't make sense with value 0\n");
		return 0;
	}
	
	return 1;
}

static struct ipt_target ipt_TTL = { { NULL, NULL }, "TTL", 
	ipt_ttl_target, ipt_ttl_checkentry, NULL, THIS_MODULE };

static int __init init(void)
{
	return ipt_register_target(&ipt_TTL);
}

static void __exit fini(void)
{
	ipt_unregister_target(&ipt_TTL);
}

module_init(init);
module_exit(fini);
