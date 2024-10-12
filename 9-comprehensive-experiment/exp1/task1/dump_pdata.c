/*
 *  The kernel module generated is: csi_dump_pdata.ko
 *  
 *  Usage:
 *     sudo insmod ./csi_dump_pdata.ko                               # using default parameters
 *     sudo insmod ./csi_dump_pdata.ko  pid=1234  filename=abcd.efg
 *     sudo rmmod    csi_dump_pdata
 *  To check if the command above runs ok, run
 *     sudo dmesg | grep CSI
 *
 *  NOTICE: the specified filename should NOT exist when issuing the commands above.
 * */

#include <linux/version.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/sched.h>
#include <linux/file.h>
#include <linux/fcntl.h>

static pid_t pid = 1;
static char *filename = "proc_data";

module_param(pid, int, 0444);
MODULE_PARM_DESC(pid, " ID of the target process (in current namespace) to be read, default to process 1;");
module_param(filename, charp, 0444);
MODULE_PARM_DESC(filename, " The file in dir /tmp to be written to (ensure it is a new file), default to /tmp/proc_data;");

#define ZPREFIX   KERN_INFO "(CSI) "

//  Since version 4.14 of Linux kernel, vfs_read and vfs_write functions are no longer exported for use in modules.
//  Use kernel_read(), kernel_write() instead:
//      ssize_t kernel_read(struct file *file, void *buf, size_t count, loff_t *pos);
//      ssize_t kernel_write(struct file *file, const void *buf, size_t count, loff_t *pos);

struct task_struct *FindTaskByPid (pid_t pid)
{
	struct task_struct *task;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
    task = find_task_by_pid(pid);
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
    task = find_task_by_vpid(pid);
#else
    // 请根据实验指导书提示，补充代码
    // task = 
#endif
	return task;
}

void CopyProcDataSection(const char *path)
{
    struct task_struct *task;
    struct file *filp;
    unsigned long uPtr, dataLen, len;
    struct page *page;
    loff_t pos = 0;
    char *kaddr;
    loff_t wLen;
    long err;

    task = FindTaskByPid(pid);
    if (task == NULL) {
        printk(ZPREFIX "Process with pid=%d not found!\n", pid);
        return;
    }
    // 请根据实验指导书提示，补充代码，对task_struct数据结构进行解析，获取进程内存的起始地址和长度
    // uPtr = 
    // dataLen = 
    len = dataLen;

    filp = filp_open(path, O_CREAT | O_WRONLY | O_NOFOLLOW | O_LARGEFILE | O_EXCL, 0644);
    if (IS_ERR(filp)) {
        printk(ZPREFIX "Fail to write-open file '%s'; exit.\n", path);
        return;
    }

    while (len > 0) {】
        // 请根据实验指导书提示，补充代码，gup_flags可用 FOLL_FORCE，vma和locked参数我们不需要，可设置为NULL
        // err = get_user_pages_remote(
        if (err < 0) {
            printk(ZPREFIX "Fail to get a remote page (userPtr=0x%lX); break.\n", uPtr);
            break;
        }
        wLen = len > PAGE_SIZE ? len - PAGE_SIZE : len;
        uPtr += wLen;
        len -= wLen;
        kaddr = kmap_atomic(page);
        err = kernel_write(filp, kaddr, wLen, &pos);
        kunmap_atomic(kaddr);
        if (err < 0) {
            printk(ZPREFIX "Fail to write to file '%s', %lu of %lu bytes written; break.\n", path, dataLen-len, dataLen);
            break;
        }
    }
    
    filp_close(filp, NULL);
    printk(ZPREFIX "done. %lu bytes written to file '%s'\n", dataLen, path);
}

static char fnBuf[4096];
static int __init my_exam_init(void)
{
    unsigned int sLen;
    char *chPtr;
    for (chPtr = filename; *chPtr != 0; chPtr++) {
        if (*chPtr == '/') {
            printk(ZPREFIX "Bad: dir name is NOT permitted in '%s'.\n", filename);
            return -EINVAL;
        }
    }
    sLen = strlen(filename);
    if (sLen > 4000) {
        printk(ZPREFIX "Bad: file name is too long.\n");
        return -ENAMETOOLONG;
    }
    sprintf(fnBuf, "/tmp/%s", filename);
    printk(ZPREFIX "To retrieve proc data section: aimed pid is %d, target filename is: '%s';\n", pid, fnBuf);
    CopyProcDataSection(fnBuf);
    return 0;
}

static void __exit my_exam_exit(void)
{
    printk(ZPREFIX "Proc data retriever: exit!\n");
}

module_init(my_exam_init);
module_exit(my_exam_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("z@HW_CSL");
MODULE_DESCRIPTION("Retrieve the first page of data section for a given process");
MODULE_VERSION("0.01");
