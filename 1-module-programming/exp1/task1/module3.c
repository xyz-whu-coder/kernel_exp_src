//read-only proc file
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry *entry;

static int hello_proc_show(struct seq_file *m, void *v) {
	seq_printf(m, "This is a proc message!!\n");
	return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init hello_proc_init(void) {
	printk("module3 is loaded!");
	//请按实验指导书要求补充完整
	//使用 proc_create 函数来创建一个只读的/proc 文件，关联的文件操作为hello_proc_fops
	entry = proc_create("hello_proc", 0x0444, NULL, &hello_proc_fops);
	
	return 0;
}

static void __exit hello_proc_exit(void) {
	printk("module3 is removed!");
	//请按实验指导书要求补充完整
	//使用remove_proc_entry 函数来删除之前创建的 /proc 文件
	// void remove_proc_entry(const char* name, struct proc_dir_entry* parent)
	remove_proc_entry("/proc/hello_proc", entry);
}

MODULE_LICENSE("GPL");
module_init(hello_proc_init);
module_exit(hello_proc_exit);
