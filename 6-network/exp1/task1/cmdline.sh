# yum install clang
clang -Wall -target bpf -c eth0.c -o eth0.o
ip link set dev eth0 xdp obj eth0.o
ip link set dev eth0 xdp off

# 虚拟机上的设备可能无法支持native模式。比如在鲲鹏云弹性云服务器ECS上运行时会出现如下错误：
# ip link set dev eth0 xdp obj eth0.o
# Error: virtio_net: Too few free TX rings available.
# 建议使用物理机。