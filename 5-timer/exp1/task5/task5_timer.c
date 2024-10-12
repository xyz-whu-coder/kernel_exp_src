#include <linux/module.h>
#include <linux/timer.h>
#include <linux/sched/signal.h>
#include <linux/mm_types.h>
#include <linux/string.h>

#define NUM_K 10

MODULE_LICENSE("GPL");

struct top_process 
{
	char comm[16];
	int pid;
	int state;
	long total_vm;
};

struct top_process topK_pro[NUM_K];
struct timer_list timer;

static void process_cpy(struct top_process *dst, struct top_process *src) 
{
	strcpy(dst->comm, src->comm);
	dst->pid = src->pid;
	dst->state = src->state;
	dst->total_vm = src->total_vm;
}

/* Maintain array top[], insert sort, and sort in descending order. */
static void sort_topK(struct top_process top[], struct top_process t)
{
	// 请按实验指导书要求补充完整 ，完成根据虚拟内存使用情况的对前10的进程排序任务
	// 可调用process_cpy函数

}

/* Print the information of the top K processes occupying the most memory. */
void printTopk(struct timer_list *timer)
{
	int i, pid, state;
	char *name;
	unsigned long mem;
	struct task_struct *p;
	struct top_process tmp_process;
	for_each_process(p){
		// 请按实验指导书要求补充完整，比较当前进程是否进入前十序列，若是，则调用排序函数sort_topK


	}
	printk("Top %d process using most memory is as follow:\n", NUM_K);
	for(i = 0; i < NUM_K; i++){
		name = topK_pro[i].comm;
		pid = topK_pro[i].pid;
		state = topK_pro[i].state;
		mem = topK_pro[i].total_vm;
		printk("1)name:%s  2)pid:%d  3)state:%d  4)mem:%lu\n", name, pid, state, mem);
	}
}

static int __init timer_MaxPro_init(void)
{
	int i;
	for(i = 0; i < NUM_K; i++)
		topK_pro[i].total_vm = 0;
	printk("timer_MaxPro init\n");
	timer.expires = jiffies + 15 * HZ;
	timer.function = printTopk;
	add_timer(&timer);
	return 0;
}

static void __exit timer_MaxPro_exit(void)
{
	printk("timer_MaxPro exit\n");
}

module_init(timer_MaxPro_init);
module_exit(timer_MaxPro_exit);
