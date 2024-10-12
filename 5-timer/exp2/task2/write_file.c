#include <linux/module.h>
#include <linux/fs.h>
#include <linux/rtc.h>
#include <linux/time.h>

#define BUF_SIZE 76
#define write_times 100000

MODULE_LICENSE("GPL");

int start_time;
int start_time_u;
int end_time;
int end_time_u;
long write_time;

static int __init write_file_init(void)
{
    struct file *file_write;
    char buf[BUF_SIZE];
    int i;  
    loff_t pos = 0;

    printk("Start file writing process !\n");

    // 请按实验指导书要求补充完整 进行内核文件操作，然后进行有效的计时
    
    
    printk("It takes %ld us to write to a file.\n", write_time);
    printk("And writing times is: %d.\n", write_times);
    return 0;
}

static void __exit write_file_exit(void)
{
    printk("Exit writing process !\n");
}

module_init(write_file_init);
module_exit(write_file_exit);
