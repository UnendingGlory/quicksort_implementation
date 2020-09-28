#ifndef MYTEST_H
#define MYTEST_H

#include <cstdlib>
#include <cstring>

#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m"
#define RED(msg)    COLOR(msg, 31)
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)

int *getRandData(int n)
{
    int *arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i)
        arr[i] = rand() % n; // random initial
    return arr;
}

bool check(int *arr, int n)
{
    for(int i = 1; i < n; ++i)
    {
        if(arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// func函数代表快速排序不同版本
#define TEST(func, arr, n) __TEST(func, #func, arr, n)

void __TEST(
    void (*func)(int *, int, int), 
    const char *func_name,
    int *arr,
    int n
){
    // 为了不破坏源数组数据
    int *temp = (int *)malloc(sizeof(int) * n);
    memcpy(temp, arr, sizeof(int) * n);

    // 记录该种快排用时
    auto start = clock();
    func(temp, 0, n - 1); // 调用不同版本的函数
    auto end = clock();

    if(check(temp, n)) // 检查排序完后的数组是否有序
    {
        printf(GREEN("[ OK  ]"));
    }
    else
    {
        printf(RED("[ FAILED  ]"));
    }
    printf("%s " YELLOW("(%lld ms)\n"), func_name, 1000 * (end -start) / CLOCKS_PER_SEC); 
    free(temp);
    return;
}

#endif