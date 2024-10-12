# make
# insmod task1_timer.ko
# lsmod | grep task1_timer
task1_timer           262144  0
# rmmod task1_timer
# dmesg -T | tail -n5
[Tue Aug  3 20:28:16 2021] task1_timer: loading out-of-tree module taints kernel.
[Tue Aug  3 20:28:16 2021] task1_timer: module verification failed: signature and/or required key missing - tainting kernel
[Tue Aug  3 20:28:16 2021] timer init
[Tue Aug  3 20:28:26 2021] hello,world!
[Tue Aug  3 20:29:17 2021] timer exit
# make clean