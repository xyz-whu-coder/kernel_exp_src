#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Theory&Model Group");
MODULE_DESCRIPTION("Use workqueue to print the time periodically");

int times;
module_param(times, int, 0644); // 用户向内核传递times参数

static struct workqueue_struct *queue = NULL;

static struct work_struct work1;
// static struct delayed_work work1;
static struct delayed_work work2;
// static struct work_struct work2;
static int i = 0;
// work handler
static void work_handler(struct work_struct *work1)
{
    struct timex txc;
    struct rtc_time tm;
    do_gettimeofday(&(txc.time));         // 得到系统时间 rtc_time_to_tm(txc.time.tv_sec,&tm);
    rtc_time_to_tm(txc.time.tv_sec, &tm); // 转变为世界协调时（UTC）

    printk("%d:\n", i);
    printk("%d-%d-%d  %d:%d:%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 8, tm.tm_min, tm.tm_sec); // 打印时间，从1900年开始计算
}
// delay work handler
static void work_handler_delay(struct work_struct *work2)
// static void work_handler_delay(struct work_struct *work2)
{
    //  请在此处填写代码，类比work_handler，实现获取系统时间rtc_time，并转换成UTC时间
    struct delayed_work *dwork = to_delayed_work(work2); 
    struct timex txc;
    struct rtc_time tm;
    do_gettimeofday(&(txc.time));         // 得到系统时间 rtc_time_to_tm(txc.time.tv_sec,&tm);
    rtc_time_to_tm(txc.time.tv_sec, &tm); // 转变为世界协调时（UTC）

    printk("this is a delay work : %d-%d-%d  %d:%d:%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 8, tm.tm_min, tm.tm_sec); // 打印时间，从1900年开始计算
}

static int init_workqueue(void)
{
    queue = create_workqueue("workqueue_test"); /*使用默认配置创建工作队列*/
    printk(KERN_ALERT "=================================\n");
    if (queue == NULL)
    {
        printk(KERN_ALERT "create workqueue_test instance error\n");
        return -1;
    }
    INIT_WORK(&work1, work_handler);       // 创建非延迟工作项
    INIT_DELAYED_WORK(&work2, work_handler_delay); // 创建延迟工作项

    // 请在此处填写代码，将创建的延迟工作项、加入工作队列
    schedule_delayed_work(&work2, 1);
    i = 0;
    for (; i < times; i++)
    {
        // 请在此处填写代码，将创建的延非延迟工作项，加入工作队列，并唤醒线程提交工作
        // printk("%d\n", times);
        queue_work(queue, &work1);
        flush_workqueue(queue);
        // schedule_work(&work1);
    }

    return 0;
}

static void exit_workqueue(void)
{
    flush_workqueue(queue);   // 冲刷工作队列以确保所有工作都完成
    destroy_workqueue(queue); // 销毁工作队列
    printk(KERN_ALERT "unloading OK\n");
}
module_init(init_workqueue);
module_exit(exit_workqueue);
