# make
# insmod task2_timer.ko
# lsmod | grep task2_timer
task2_timer           262144  0
# rmmod task2_timer
# dmesg -T | tail -n25
[Tue Aug  3 20:35:37 2021] timer init
[Tue Aug  3 20:35:38 2021] 1th second
[Tue Aug  3 20:35:39 2021] 2th second
[Tue Aug  3 20:35:41 2021] 3th second
[Tue Aug  3 20:35:42 2021] 4th second
[Tue Aug  3 20:35:43 2021] 5th second
[Tue Aug  3 20:35:44 2021] 6th second
[Tue Aug  3 20:35:45 2021] 7th second
[Tue Aug  3 20:35:46 2021] 8th second
[Tue Aug  3 20:35:47 2021] 9th second
[Tue Aug  3 20:35:48 2021] 10th second
[Tue Aug  3 20:35:49 2021] 11th second
[Tue Aug  3 20:35:50 2021] 12th second
[Tue Aug  3 20:35:51 2021] 13th second
[Tue Aug  3 20:35:52 2021] 14th second
[Tue Aug  3 20:35:53 2021] hello,world!
[Tue Aug  3 20:35:53 2021] 15th second
[Tue Aug  3 20:36:19 2021] timer exit
# make clean