# make
# make install
insmod task3_timer.ko
# make uninstall
rmmod task3_timer
# dmesg | tail -n6
[  910.093452] timer init
[  910.093676] Timer is added.
[  910.093679] Current time:2021-08-03 20:41:33
[  918.248822] Timer is deleted.
[  918.248825] Current time:2021-08-03 20:41:41
[  981.000392] timer exit
# make clean