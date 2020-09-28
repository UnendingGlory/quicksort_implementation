// 对快速排序不同版本进行测试
#include <iostream>
#include "mytest.h"
#include "quicksort.h"

int main()
{
    #define MAX_N 1000000
    int *arr = getRandData(MAX_N);
    TEST(quicksort_v1, arr, MAX_N);
    #undef MAX_N
    // 定义了局部变量宏要undef掉，为了协同工作
    return 0;
}