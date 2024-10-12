# make
# make install
insmod task4_timer.ko
# lsmod |grep task4_timer
task4_timer           262144  0
# make uninstall
rmmod task4_timer
# dmesg | tail -30
[ 1161.163115] maxPro init
[ 1161.163341] 1)name:systemd  2)pid:1  3)state:1  4)mem:2706
[ 1161.163728] 1)name:systemd-journal  2)pid:462  3)state:1  4)mem:887
[ 1161.164151] 1)name:systemd-udevd  2)pid:478  3)state:1  4)mem:535
[ 1161.164562] 1)name:auditd  2)pid:1201  3)state:1  4)mem:312
[ 1161.164945] 1)name:dbus-daemon  2)pid:1298  3)state:1  4)mem:150
[ 1161.165352] 1)name:NetworkManager  2)pid:1299  3)state:1  4)mem:8540
[ 1161.165798] 1)name:polkitd  2)pid:1306  3)state:1  4)mem:25922
[ 1161.166190] 1)name:rngd  2)pid:1309  3)state:1  4)mem:317
[ 1161.166557] 1)name:rsyslogd  2)pid:1316  3)state:1  4)mem:3862
[ 1161.166959] 1)name:irqbalance  2)pid:1333  3)state:1  4)mem:1266
[ 1161.167479] 1)name:chronyd  2)pid:1334  3)state:1  4)mem:1247
[ 1161.168379] 1)name:systemd-network  2)pid:1351  3)state:1  4)mem:358
[ 1161.169263] 1)name:systemd-logind  2)pid:1456  3)state:1  4)mem:351
[ 1161.170133] 1)name:tuned  2)pid:1490  3)state:1  4)mem:7384
[ 1161.170932] 1)name:dhclient  2)pid:1517  3)state:1  4)mem:291
[ 1161.171826] 1)name:sshd  2)pid:1945  3)state:1  4)mem:262
[ 1161.172574] 1)name:crond  2)pid:1950  3)state:1  4)mem:3373
[ 1161.173304] 1)name:agetty  2)pid:1951  3)state:1  4)mem:3334
[ 1161.174049] 1)name:agetty  2)pid:1952  3)state:1  4)mem:3327
[ 1161.174774] 1)name:sshd  2)pid:1974  3)state:1  4)mem:351
[ 1161.175576] 1)name:systemd  2)pid:2133  3)state:1  4)mem:381
[ 1161.176288] 1)name:(sd-pam)  2)pid:2135  3)state:1  4)mem:500
[ 1161.177017] 1)name:sshd  2)pid:2141  3)state:1  4)mem:351
[ 1161.177747] 1)name:bash  2)pid:2142  3)state:1  4)mem:3359
[ 1161.178462] 1)name:hostguard  2)pid:2204  3)state:1  4)mem:192
[ 1161.179272] 1)name:hostguard  2)pid:2206  3)state:1  4)mem:19839
[ 1161.180034] 1)name:make  2)pid:5280  3)state:1  4)mem:3464
[ 1161.180771] 1)name:insmod  2)pid:5282  3)state:0  4)mem:63
[ 1249.167979] maxPro exit
# make clean