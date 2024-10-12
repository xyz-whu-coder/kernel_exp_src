#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/rtc.h>
#include <linux/time.h>

struct timespec64 ts;

int start_bubble_sort;
int start_bubble_sort_u;
int end_bubble_sort;
int end_bubble_sort_u;

long int bubble_sort_time;

#define BUF_SIZE 1000
static char buf[BUF_SIZE] = {'\0'};

MODULE_LICENSE("GPL");

void swap_num(int * a,int * b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void bubble_sort(int num[],int begin,int end)
{
    // 请按实验指导书要求补充完整，完成一个简单的冒泡排序，使用swap_num函数
}

static int charToInt(char a[], int n)
{
    int ret = a[n-1]-'0';
    int i = n - 2;
    int carry = 1;
    for(;i >= 0; i--){
        carry *= 10;
        ret += (a[i]-'0') * carry;
    }
    return ret;
}

static int read_file(void)
{
    struct file *fp_file;
    loff_t pos = 0;
    fp_file = filp_open("./file", O_RDONLY, 0644);
    if (IS_ERR(fp_file)){
        printk("Failed to open file.\n");
        return -1;
    }
    kernel_read(fp_file, buf, BUF_SIZE, &pos);
    filp_close(fp_file, NULL);
    return 0;
}

static int __init module_start(void)
{
    char result[20] ={'\0'};
    int sort_num[100];
    int result_int;
    int length;
    int total_num = 0;
    int i = 0;
    int step = 0;
    int j = 0;

    printk("Start bubble sort module !");
    if(read_file()){
        printk("Failed to open file.\n");
        return -1;
    }else{
        while( buf[i] != '\0' ){
            if(buf[i] != ' '){
                result[step++] = buf[i];
            }else{
                length = strlen(result);
                result_int = charToInt(result, length);
                sort_num[total_num] = result_int;
                memset(result,'\0',20);
                step = 0;
                total_num++;
            }
            i++;
        }
        if( buf[i] == '\0' ){
            length = strlen(result);
            result_int = charToInt(result, length);
            sort_num[total_num] = result_int;
            memset(result,'\0',20);
            step = 0;
            total_num++;
        }
    }
    // *****************测试冒泡排序消耗的时间**********
    // 请按实验指导书要求补充完整，测试冒泡排序的时间  



    
    printk("After bubble sort, current time is %d s  %d  us", end_bubble_sort, end_bubble_sort_u);
    bubble_sort_time = (end_bubble_sort - start_bubble_sort) * 1000000  + (end_bubble_sort_u - start_bubble_sort_u);
    printk("Bubble sort takes %ld us ", bubble_sort_time);
    printk("The result after bubble sort is :\n");
    for(j = 0; j < total_num; j++)
        printk("%d", sort_num[j]);

    return  0;
}

static void __exit module_leave(void)
{
    printk("Exit sort module !");
}

module_init(module_start);
module_exit(module_leave);
