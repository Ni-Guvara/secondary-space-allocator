SGI-STL的二级空间配置器是基于自由链表实现，主要用于对小于等于128字节的小型字节块进行分配与回收。

主要函数包含，

```cpp
static void* allocate(size_t __n)  // 内存分配的接口
static void deallocate(void* __p, size_t __n)  // 内存释放的接口
static size_t _S_round_up(size_t __bytes) // 得到某个字节数向上最接近的8的倍数
static size_t _S_freelist_index(size_t __bytes) // 得到某个字节数在自由链表的索引位置
static void* _S_refill(size_t __n) // 将得到的内存块进行组织
static char* _S_chunk_alloc(size_t __size, int& __nobjs) // 获取内存块
```

1. `static void* _S_refill(size_t __n)`函数将获取到的内存块根据在自由链表数组上的定位，将返回地址存储在定位得到索引位置。需要注意的是，其存储的不是得到内存块第一个块而是从第二块开始，并通过链表将块串联到一块。

2. `static char* _S_chunk_alloc(size_t __size, int& __nobjs)`，主要由三个部分组成，其剩余的内存完全可以满足内存池需要扩展的内存、其剩余内存可以部分满足内存池需要扩展的内存、完全不能满足内存池需要的内存。

   **在第三种情况下，当剩余的内存容量存在但是不满足所需要块的大小，会将该剩余的小块内存(粒度对齐，为8的倍数)，配分给其对应的自由链表索引位置的链表中。**之后，进行内存获取，其扩展为原来内存大小的二倍多。更新一些静态变量且返回地址。

   