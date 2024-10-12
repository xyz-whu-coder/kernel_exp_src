#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/rtc.h>
#include <linux/time.h>

struct timespec64 ts;

int start_quick_sort;
int start_quick_sort_u;
int end_quick_sort;
int end_quick_sort_u;

long int quick_sort_time;

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

static int parti(int num[], int  begin , int  end)
{
    int i,j;
    int pivot = num[end];
    //random pivot
    j = begin;
    i = j-1;
    for(; j < end; ++j){
        if(num[j] < pivot){
            i++;
            swap_num(&num[i],&num[j]);
        }
    }
    i = i+1;
    swap_num(&num[i],&num[j]);
    return i;
}

static void quick_sort(int num[],int begin ,int end)
{
    // 请按实验指导书要求补充完整，完成一个快速排序
}

static int charToInt(char a[], int n)
{
    int ret = a[n-1]-'0';
    int i = n - 2;
    int carry = 1;
    for(; i >= 0; i--){
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
    if (IS_ERR(fp_file)) {
        printk("Failed to open file.\n");
        return -1;
    }
    kernel_read(fp_file, buf, BUF_SIZE, &pos);
    filp_close(fp_file, NULL);
    return 0;
}

static int __init module_start(void)
{
    char result[20] = {'\0'};
    int sort_num[100];
    int result_int;
    int length;
    int total_num = 0;
    int i = 0;
    int j = 0;
    int step = 0;

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
    // ****************测试快排的消耗时间**************
    printk("Start quick sort module !");
    // 请按实验指导书要求补充完整，同冒泡的要求，补充代码，计算排序耗时



    printk("Before quick sort, current time is %d s  %d us", start_quick_sort, start_quick_sort_u);

    quick_sort(sort_num, 0, total_num-1);

    ktime_get_real_ts64(&ts);
    end_quick_sort = (int)ts.tv_sec;
    end_quick_sort_u = (int)ts.tv_nsec / 1000;
    quick_sort_time = (end_quick_sort - start_quick_sort) * 1000000  + (end_quick_sort_u - start_quick_sort_u);
    printk("After quick sort, current time is %d s  %d us", end_quick_sort, end_quick_sort_u);
    printk("Quick sort takes %ld us ", quick_sort_time);
    printk("The result after quick sort is :\n");
    for(j = 0; j < total_num; j++)
        printk(" %d",sort_num[j]);

    return  0;
}

static void __exit module_leave(void)
{
    printk("Exit quick sort module !");
}

module_init(module_start);
module_exit(module_leave);
