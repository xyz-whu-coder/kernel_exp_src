/* High-level overview: This works by maintaining a singly-linked list
 * of previously-used memory segments that have been freed. */

#define NALLOC 1024

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

/* This header is stored at the beginning of memory segments in the list. */
union header {
  struct {
    union header *next;
    unsigned len;
  } meta;
  long x; /* Presence forces alignment of headers in memory. */
};

static union header list;
static union header *first = NULL;

void free(void* ptr) {
  if (ptr == NULL) {
    return;
  }

  union header *iter, *block;
  iter = first;
  block = (union header*)ptr - 1;

  /* Traverse to the spot in the list to insert the freed fragment,
   * such that the list is ordered by memory address (for coalescing). */
  while (block <= iter || block >= iter->meta.next) {
    if ((block > iter || block < iter->meta.next) &&
        iter >= iter->meta.next) {
      break;
    }
    iter = iter->meta.next;
  }

  /* If the new fragment is adjacent in memory to any others, merge
   * them (we only have to check the adjacent elements because the
   * order semantics are enforced). */
  if (block + block->meta.len == iter->meta.next) {
    block->meta.len += iter->meta.next->meta.len;
    block->meta.next = iter->meta.next->meta.next;
  } else {
    block->meta.next = iter->meta.next;
  }
  if (iter + iter->meta.len == block) {
    iter->meta.len += block->meta.len;
    iter->meta.next = block->meta.next;
  } else {
    iter->meta.next = block;
  }

  first = iter;
}

void *emalloc(size_t size) {
  // 请按实验指导书要求补充完整 emalloc 函数的实现
}

void* calloc(size_t num, size_t len) {
  void* ptr = emalloc(num * len);

  /* Set the allocated array to 0's.*/
  if (ptr != NULL) {
    memset(ptr, 0, num * len);
  }

  return ptr;
}

void* realloc(void *ptr, size_t new_size) {
  size_t old_size = 0; /* XXX yolo */
  void* new = emalloc(new_size);

  if (new == NULL) {
    /* emalloc() failed, insufficient memory remaining. */
    errno = ENOMEM;
  } else {
    /* We cannot grow the memory segment. */
    if (new_size > old_size) {
      new_size = old_size;
    }
    memmove(new, ptr, new_size);
    free(ptr);
  }

  return new;
}

