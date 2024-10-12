# make
# insmod sum_time.ko
# lsmod |grep sum_time
sum_time              262144  0
# rmmod sum_time
# dmesg |tail -n6
[  126.370747] Start sum process !
[  126.370963] The start time is: 1627996748 s 630657 us
[  126.371313] The sum of 1 to 100000 is: 5000050000
[  126.371724] The end time is: 1627996748 s 631418 us
[  126.372062] The cost time of sum from 1 to 100000 is: 761 us
[  147.274091] Exit sum process !
# make clean