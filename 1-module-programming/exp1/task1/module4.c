#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>       // for basic filesystem
#include <linux/proc_fs.h>  // for the proc filesystem
#include <linux/seq_file.h> // for sequence files
#include <linux/slab.h>     // for kzalloc, kfree
#include <linux/uaccess.h>  // for copy_from_user
#define BUF_SIZE 10
// global var
static char *str = NULL;
static int curr_len = 0;
static struct proc_dir_entry *parent;

// seq_operations -> show
static int hello_show(struct seq_file *m, void *v)
{
    seq_printf(m, "This is proc message from module4\n");
    seq_printf(m, "str is %s\n", str);

    return 0;
}

// file_operations -> write
static ssize_t hello_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    // 请按实验指导书要求补充完整
    char *tmp;
    size_t bytes_copied;
    size_t new_len;
    // 使用 kzalloc 分配内核空间临时缓冲区tmp
    // void *kmalloc(size_t size, gfp_t flags)；
    tmp = kzalloc(count + 1, GFP_KERNEL);
    if (tmp == NULL) {  
        printk(KERN_ERR "Failed to allocate memory\n");  
        return -ENOMEM;  
    }
    // 使用copy_from_user函数，拷贝用户缓冲buffer内容，到内核空间内存tmp
    bytes_copied = copy_from_user(tmp, buffer, count);
    if (bytes_copied != 0) {
        printk(KERN_ERR "Failed to copy from user space, bytes_copied = %lu\n", bytes_copied);
        kfree(tmp);
        return -ENOMEM;
    }
    tmp[count] = '\0';
    // 将tmp缓冲区接收到的内容，拼接到内核全局变量str的末尾，，curr_len为str的总长度，注意边界检查
    new_len = curr_len + count;
    if (new_len > BUF_SIZE) {
        printk(KERN_ERR "String overflow\n");
        kfree(tmp);
        return -ENOMEM;
    }

    if (str) {  
        strncat(str, tmp, count);  
    } else {  
        // 如果str是NULL（这通常不应该发生，除非在模块加载时没有正确初始化），则分配并复制  
        str = kzalloc(new_len + 1, GFP_KERNEL);  // +1 for null terminator  
        if (!str) {  
            printk(KERN_ERR "Failed to allocate memory for str\n");  
            kfree(tmp);  
            return -ENOMEM;  
        }  
        strncpy(str, tmp, count);  
    }  
    curr_len = new_len;

    printk(KERN_INFO "current len is %d", curr_len);

    kfree(tmp);
    count -= bytes_copied;

    return count;
}

// seq_operations -> open
static int hello_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_show, NULL);
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .read = seq_read,
    .write = hello_write,
    .llseek = seq_lseek,
    .release = single_release,
};

// module init
static int __init hello_init(void)
{
    struct proc_dir_entry *hello_file;
    parent = proc_mkdir("hello_dir", NULL);
    hello_file = proc_create("hello", 0, parent, &hello_fops);
    if (NULL == hello_file)
    {
        return -ENOMEM;
    }

    return 0;
}

// module exit
static void __exit hello_exit(void)
{
    remove_proc_entry("hello", NULL);
    remove_proc_entry("hello_dir", NULL);
    kfree(str);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
