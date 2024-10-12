# make
# insmod write_file.ko
# lsmod |grep write_file
write_file            262144  0
# rmmod write_file
# dmesg |tail -n4
[  260.024003] Start file writing process !
[  260.138383] It takes 114025 us to write to a file.
[  260.138750] And writing times is: 100000.
[  276.671827] Exit writing process !
# make clean
# cat /home/output_file100000.txt
0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz
0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz
0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz
......