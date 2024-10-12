#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched/signal.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/kthread.h>

static struct task_struct *cycleprint_kthread = NULL;
struct task_struct *tmp_p;
char tmp_cpu_load[5] = "";
char tmp_mem_total[20] = "";
char tmp_mem_free[20] = ""; 
static char* info = "你好\n";

static int write_file(void)
{
	// 请在此处填写代码，将 info 写入文件 "/home/kernel_file" 中
    // 提示：使用 filp_open、kernel_write 和 filp_close 等函数
    return 0;
}
static void sleep_milli_sec(int n_milli_sec) {
	long timeout = (n_milli_sec)*HZ/1000;
	do {
    while(timeout > 0) {
		    timeout = schedule_timeout(timeout);
    }
	} while(0);
}

static int atoi(char a[], int n) 
{
	int ans = a[0] - '0';
	int i = 1;
	for(;i < n; i++) 
		ans = ans * 10 + (a[i] - '0');
	return ans;
}
static int load_kenerl_info(void) 
{
    struct file *fp_cpu, *fp_mem;
    loff_t pos;
	char buf_cpu[10];
	char buf_mem[100]; 
	int i = 0;
	int j = 0;
	//补充代码，使用flip_open，打开 "/proc/loadavg"，返回值赋值fp_cpu

	
	//补充代码，使用flip_open，打开 "/proc/meminfo"，返回值赋值fp_mem

	

	// 请在此处填写代码，kernel_read 读取 fp_cpu, fp_mem 指向文件中的信息
    pos = 0;

	pos = 0;

	strncpy(tmp_cpu_load, buf_cpu, 4);
	for(; i <= 99; i++)
	{
		if (buf_mem[i] >= '0' && buf_mem[i] <= '9')
		{	
			tmp_mem_total[j] = buf_mem[i];
			j++;
		}
		if (buf_mem[i] == '\n')
		{
			i++;
			break;
		}
	} 
	for(j = 0; i <= 99; i++)
	{
		if (buf_mem[i] >= '0' && buf_mem[i] <= '9')
		{
			tmp_mem_free[j] = buf_mem[i];
			j++;
		}
		if (buf_mem[i] == '\n')
			break;
	} 	
	filp_close(fp_cpu, NULL);
    filp_close(fp_mem, NULL);
    return 0;
}

static int print_fun(void *data) 
{
	write_file();
	while(!kthread_should_stop()) 
	{
		if(load_kenerl_info() != 0)
		{
			printk("read meminfo or loadarvg file error!\n"); 
			return -1;
		}
		for_each_process(tmp_p) 
		{
			if(tmp_p->state == 0) 
				printk("p name:%s, pid is:%d\n", tmp_p->comm, tmp_p->pid);
		}
		printk("the cpu load is: %s\n", tmp_cpu_load);	
		printk("total memory is: %s KB\n", tmp_mem_total);
		printk("free memory is: %s KB\n", tmp_mem_free);	
		printk("occupy memory is: %d KB\n", atoi(tmp_mem_total, strlen(tmp_mem_total)) - atoi(tmp_mem_free, strlen(tmp_mem_free)));
		sleep_milli_sec(3000);
	}
	return 0;
}

static int __init proc_parser_init(void)
{
	cycleprint_kthread = kthread_run(print_fun, NULL, "cycle_print_kthread");
	return 0;
}

static void __exit proc_parser_exit(void)
{
    if(cycleprint_kthread)
	{
		printk("stop thread: cycle_print_kthread\n");
		kthread_stop(cycleprint_kthread);
	}
	printk("proc_parser exit\n");
}
 
module_init(proc_parser_init);
module_exit(proc_parser_exit);
MODULE_LICENSE("GPL");
