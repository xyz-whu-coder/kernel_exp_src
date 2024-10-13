/* High-level overview: This works by maintaining a singly-linked list
 * of previously-used memory segments that have been freed. */

#define NALLOC 1024

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

/* This header is stored at the beginning of memory segments in the list. */
union header
{
    struct
    {
        union header *next;
        unsigned len;
    } meta;
    long x; /* Presence forces alignment of headers in memory. */
};

static union header list;
static union header *first = NULL;

void free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    union header *iter, *block;
    iter = first;
    block = (union header *)ptr - 1;

    /* Traverse to the spot in the list to insert the freed fragment,
     * such that the list is ordered by memory address (for coalescing). */
    while (block <= iter || block >= iter->meta.next)
    {
        if ((block > iter || block < iter->meta.next) &&
            iter >= iter->meta.next)
        {
            break;
        }
        iter = iter->meta.next;
    }

    /* If the new fragment is adjacent in memory to any others, merge
     * them (we only have to check the adjacent elements because the
     * order semantics are enforced). */
    if (block + block->meta.len == iter->meta.next)
    {
        block->meta.len += iter->meta.next->meta.len;
        block->meta.next = iter->meta.next->meta.next;
    }
    else
    {
        block->meta.next = iter->meta.next;
    }
    if (iter + iter->meta.len == block)
    {
        iter->meta.len += block->meta.len;
        iter->meta.next = block->meta.next;
    }
    else
    {
        iter->meta.next = block;
    }

    first = iter;
}

void *emalloc(size_t size)
{
    size_t 

}

void *emalloc(size_t size)
{
    // 请按实验指导书要求补充完整 emalloc 函数的实现
    // 转换请求的大小，确保能够容纳头部信息，并保持对齐
    size_t asize = (size + sizeof(union header) - 1) / sizeof(union header) + 1;
    union header *p, *prevp = NULL;

    // 遍历空闲内存块链表，寻找足够大的块
    for (p = first; p != NULL; prevp = p, p = p->meta.next)
    {
        if (p->meta.len >= asize)
        { // 找到一个足够大的块
            if (p->meta.len == asize)
            { // 完美匹配，不需要分割
                if (prevp == NULL)
                { 
                    // p 是链表的第一个元素
                    first = p->meta.next;
                }
                else
                {
                    prevp->meta.next = p->meta.next;
                }
            }
            else
            { // 需要分割内存块
                union header *q = (union header *)((char *)p + asize * sizeof(union header));
                q->meta.len = p->meta.len - asize;
                q->meta.next = p->meta.next;
                p->meta.len = asize;
                p->meta.next = q; // 将分割后的剩余部分链接回链表
                // if (prevp == NULL) { // 如果 p 是链表的头节点，且被分割，则更新头节点（但通常不会，因为头节点不会完美匹配）
                // 这里实际上不需要更新 first，因为我们已经将 q 链接到了 p 之后
                // 但为了保持逻辑清晰，可以保留此检查（尽管它在实际中不会被触发）
                // }
                // 注意：我们不更新 first，因为分割后的块仍在链表中，由 q 链接
            }
            return (void *)((char *)p + sizeof(union header)); // 返回用户数据的起始地址（跳过头部）
        }
    }

    // 未找到合适的空闲块，使用 sbrk 扩展堆内存
    char *brk_ptr = (char *)sbrk(asize * sizeof(union header));
    if (brk_ptr == (char *)-1)
    {                
        // sbrk 调用失败
        return NULL; // 返回 NULL 表示内存分配失败
    }

    // 初始化新分配的内存块，并将其插入链表头部（首次适应算法的简化实现）
    p = (union header *)brk_ptr;
    p->meta.len = asize;
    p->meta.next = first;
    first = p;

    return (void *)((char *)p + sizeof(union header)); // 返回用户数据的起始地址（跳过头部）
}

void *calloc(size_t num, size_t len)
{
    void *ptr = emalloc(num * len);

    /* Set the allocated array to 0's.*/
    if (ptr != NULL)
    {
        memset(ptr, 0, num * len);
    }

    return ptr;
}

void *realloc(void *ptr, size_t new_size)
{
    size_t old_size = 0; /* XXX yolo */
    void *new = emalloc(new_size);

    if (new == NULL)
    {
        /* emalloc() failed, insufficient memory remaining. */
        errno = ENOMEM;
    }
    else
    {
        /* We cannot grow the memory segment. */
        if (new_size > old_size)
        {
            new_size = old_size;
        }
        memmove(new, ptr, new_size);
        free(ptr);
    }

    return new;
}
