#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/timer.h>
#include <linux/rtc.h>

#define IS_LEAP_YEAR(year) !(year % 400) || (year % 100 && !(year % 4))
struct proc_dir_entry *time_dir;
static int mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int hello_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello proc\n");
    return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
    .owner = THIS_MODULE,
    .open = hello_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int time_proc_show(struct seq_file *m, void *v)
{
    
    struct timeval tv;
    struct rtc_time tm;
    int year, month, day, hour;
    int carry = 0;
    // 请在此处根据要求补齐代码，获取当前时间，并使用seq_print格式化输出到seq_file m中。
  

    return 0;
}

static int time_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, time_proc_show, NULL);
}

static const struct file_operations time_proc_fops = {
    .owner = THIS_MODULE,
    .open = time_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init time_proc_init(void)
{
    proc_create("hello", 0, NULL, &hello_proc_fops);
    time_dir = proc_mkdir("show_time", NULL);
    proc_create("proc_time", 0, time_dir, &time_proc_fops);
    return 0;
}

static void __exit time_proc_exit(void)
{
    remove_proc_entry("hello", NULL);
    remove_proc_entry("proc_time", time_dir);
    remove_proc_entry("show_time", NULL);
}

MODULE_LICENSE("GPL");
module_init(time_proc_init);
module_exit(time_proc_exit);
