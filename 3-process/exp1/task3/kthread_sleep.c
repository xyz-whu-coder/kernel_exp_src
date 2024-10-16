#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

struct task_struct *old_thread;

int my_function(void *argc)
{
    int data = -1;
    printk("the sub_thrread pid is:%d\n", current->pid);
    printk("the state of the init function is :%ld\n", old_thread->state);
    // 补全代码 唤醒 old_thread
    data = wake_up_process(old_thread);

    printk("the state of the init function after wake_up_process is :%ld\n", old_thread->state);
    printk("the result of the wake_up_process is:%d\n", data);
    return 0;
}

static int __init wake_up_process_init(void)
{
    char namefrm[] = "wake_up_process";
    int result_data = -1;
    long time_out;
    struct task_struct *result;
    result = kthread_create_on_node(my_function, NULL, -1, namefrm);
    printk("the pid of the sub_thread is:%d\n", result->pid);
    printk("the current pid is:%d\n", current->pid);
    old_thread = current;
    result_data = wake_up_process(result);
    printk("the result of wake_up_process for new thread is: %d\n", result_data);
    // 补全代码，使用schedule_timeout_uninterruptible（）让当前进程进入睡眠状态
    result_data = schedule_timeout_uninterruptible(time_out);
    result_data = wake_up_process(current); // 唤醒当前进程，若成功，说明该进程不处于Running状态
    printk("the result of wake_up_process for init thread is: %d\n", result_data);
    return 0;
}

static void __exit wake_up_process_exit(void)
{
    printk("Goodbye wake_up_process\n");
}

module_init(wake_up_process_init);
module_exit(wake_up_process_exit);
