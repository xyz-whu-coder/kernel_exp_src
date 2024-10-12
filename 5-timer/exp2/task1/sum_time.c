#include <linux/module.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");

#define NUM 100000

static long sum(int num)
{
    int i;
    long total = 0;
    for (i = 1; i <= NUM; i++)
        total = total + i;
    printk("The sum of 1 to %d is: %ld\n", NUM, total);
    return total;
}

static int __init sum_init(void)
{
    int start;
    int start_u;
    int end;
    int end_u;
    long time_cost;
    long s;

    struct timespec64 ts;
    printk("Start sum process !\n");
    // 请按实验指导书要求补充完整，获取时间，并在计算完成后进行相应计算

    printk("The end time is: %d s %d us \n", end, end_u);
    // 填充计算的代码
    // time_cost = 
    
    printk("The cost time of sum from 1 to %d is: %ld us \n", NUM, time_cost);
    return 0;
}

static void __exit sum_exit(void)
{
    printk("Exit sum process !\n");
}

module_init(sum_init);
module_exit(sum_exit);
