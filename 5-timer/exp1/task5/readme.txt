# make
# make install
insmod task5_timer.ko
# make uninstall
rmmod task5_timer
[root@kunpeng task5]# dmesg | tail -n13
[ 1446.130286] timer_MaxPro init
[ 1461.220837] Top 10 process using most memory is as follow:
[ 1461.221784] 1)name:polkitd  2)pid:1306  3)state:1  4)mem:25922
[ 1461.222612] 1)name:hostguard  2)pid:2206  3)state:1  4)mem:19839
[ 1461.223460] 1)name:NetworkManager  2)pid:1299  3)state:1  4)mem:8540
[ 1461.224322] 1)name:tuned  2)pid:1490  3)state:1  4)mem:7384
[ 1461.225152] 1)name:rsyslogd  2)pid:1316  3)state:1  4)mem:3862
[ 1461.226002] 1)name:crond  2)pid:1950  3)state:1  4)mem:3373
[ 1461.226837] 1)name:bash  2)pid:2142  3)state:1  4)mem:3359
[ 1461.227664] 1)name:agetty  2)pid:1951  3)state:1  4)mem:3334
[ 1461.228514] 1)name:agetty  2)pid:1952  3)state:1  4)mem:3327
[ 1461.229355] 1)name:systemd  2)pid:1  3)state:1  4)mem:2706
[ 1490.685015] timer_MaxPro exit
[root@kunpeng task5]# make clean