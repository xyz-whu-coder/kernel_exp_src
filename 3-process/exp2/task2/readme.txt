# make
# make install
insmod proc_time.ko
# cat /proc/show_time/proc_time
UTC time :2021-8-1 19:20:39
# lsmod |grep proc_time
proc_time             262144  0
# make uninstall
rmmod proc_time
# cat /proc/show_time/proc_time
cat: /proc/show_time/proc_time: No such file or directory
# make clean
