转储进程数据段的内核模块编程。

# make

# insmod csi_dump_pdata.ko #不带参数装载模块
# lsmod |grep csi_dump_pdata
csi_dump_pdata              262144  0
# rmmod csi_dump_pdata
# dmesg | tail -n5
[  427.711314] csi_dump_pdata: loading out-of-tree module taints kernel.
[  427.711834] csi_dump_pdata: module verification failed: signature and/or required key missing - tainting kernel
[  427.712995] (CSI) To retrieve proc data section: aimed pid is 1, target filename is: '/tmp/proc_data';
[  427.713777] (CSI) done. 282728 bytes written to file '/tmp/proc_data'
[  526.804488] (CSI) Proc data retriever: exit!

# insmod csi_dump_pdata.ko pid=10364 filename=i_pdata.elf #带参数装载模块
# rmmod csi_dump_pdata

# make clean

注意：加载模块时，若不带参数则使用默认值。可以通过进程号指定某一进程。进程号pid可由“ps -ef | grep your-task-name”命令获取，请将上述“your-task-name”字样替换为您自己想要查看的进程的名字。转存后的文件在/tmp目录下。
