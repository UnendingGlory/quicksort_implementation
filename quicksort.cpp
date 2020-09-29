// 对快速排序不同版本进行测试
#include <iostream>
#include "mytest.h"
#include "quicksort.h"


int main()
{
    srand(time(0));
    
    // 无序序列
    printf(RED("Unordered sequence:\n"));
    #define MAX_N 1000000
    int *arr = getRandData(MAX_N);
    TEST(quicksort_v1, arr, MAX_N);
    TEST(quicksort_v2, arr, MAX_N);
    // 插排的时间复杂度较高，所以降低点数据量
    #define LESS_N 10000
    TEST(insertsort, arr, LESS_N);
    TEST(unguarded_insertsort, arr, LESS_N);
    #undef LESS_N

    TEST(quicksort_v3, arr, MAX_N);
    TEST(quicksort_v4, arr, MAX_N);
    TEST(quicksort_v5, arr, MAX_N);
    TEST(quicksort_v6, arr, MAX_N);
    #undef MAX_N
    // 定义了局部变量宏要undef掉，为了协同工作

    // 有序序列，快排退化，所以要降低数据量
    printf(RED("Ordered sequence:\n"));
    #define MAX_N 10000
    arr = getOrderedData(MAX_N);
    TEST(quicksort_v1, arr, MAX_N);
    TEST(quicksort_v2, arr, MAX_N);

    // 对于有序序列，插排就是o(n)
    TEST(insertsort, arr, MAX_N);
    TEST(unguarded_insertsort, arr, MAX_N);

    TEST(quicksort_v3, arr, MAX_N);
    TEST(quicksort_v4, arr, MAX_N);
    TEST(quicksort_v5, arr, MAX_N);
    TEST(quicksort_v6, arr, MAX_N);
    #undef MAX_N

    return 0;
}