#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

#define __section(NAME) __attribute__((section(NAME), used))

__section("prog") int drop_tcp(struct xdp_md *ctx)
{
    int ipsize = 0;

    void *data = (void *)(long)ctx->data;
    struct iphdr *ip;

    ip = data + sizeof(struct ethhdr);

    if (ip->protocol == IPPROTO_TCP)
    {
        //请增加这里的代码，丢弃TCP数据包

    }

    //请增加这里的代码，除了TCP数据包外，都放行


}

char _license[] __section("license") = "GPL";

