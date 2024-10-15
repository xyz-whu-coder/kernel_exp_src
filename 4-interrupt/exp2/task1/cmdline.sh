ls
# Makefile  workqueue_test.c
make
insmod workqueue_test.ko times=5
lsmod |grep workqueue_test
# workqueue_test        262144  0
rmmod workqueue_test
dmesg | tail -n15
# [12503.319760] 0:
# [12503.319761] 2021-8-3  17:40:50
# [12508.388953] 1:
# [12508.388955] 2021-8-3  17:40:55
# [12513.508898] this is a delay work : 2021-8-3  17:41:0
# [12513.509737] 2:
# [12513.509738] 2021-8-3  17:41:0
# [12518.628862] 3:
# [12518.628864] 2021-8-3  17:41:5
# [12523.748841] 4:
# [12523.748843] 2021-8-3  17:41:10
# [12556.120925] unloading OK
make clean
