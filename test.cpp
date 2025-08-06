#include <iostream>
#include "SecondarySpaceAllocator.h"

int main()
{
    int* p = (int*)SecondarySpaceAllocator::_allocate(8);
    *p = 8;
    std::cout <<"size:" << sizeof(*p) << ","; 
    std::cout <<"content:" <<  *p << std::endl;
    SecondarySpaceAllocator::_deallocate(p, sizeof(p));
}