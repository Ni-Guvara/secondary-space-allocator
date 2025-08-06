#ifndef SECONDARYSPACEALLOCATOR_H
#define SECONDARYSPACEALLOCATOR_H

#include<stdlib.h>

union _Obj {
        union _Obj* _M_free_list_link;
        char _M_client_data[1];    
};


class SecondarySpaceAllocator{


        enum {_ALIGN = 8};
        enum {_MAX_BYTES = 128};
        enum {_NFREELISTS = 16}; 

        static char* _S_start_free;
        static char* _S_end_free;
        static size_t _S_heap_size;
        static _Obj*  _S_free_list[_NFREELISTS]; 


    public:
        static  size_t _S_freelist_index(size_t __bytes);

        static size_t _S_round_up(size_t __bytes);
      
        static void* _allocate(size_t __n);

        static void _deallocate(void* __p, size_t __n);

        static void* _S_refill(size_t __n);

        static char* _S_chunk_alloc(size_t __size, int& __nobjs);

};



#endif