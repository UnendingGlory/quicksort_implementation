#include <algorithm>

/*
 * 最简单的快速排序版本，patition + 递归
 */
void quicksort_v1(int *arr, int l, int r)
{
    if(l >= r) return;
    // 下面开始partition操作，枢轴元素选取最左边
    int x = l, y = r, temp = arr[l];
    while(x < y)
    {
        while(x < y && arr[y] >= temp) --y;
        if(x < y) arr[x] = arr[y];
        while(x < y && arr[x] <= temp) ++x;
        if(x < y) arr[y] = arr[x];
    }
    arr[x] = temp;
    quicksort_v1(arr, l, x - 1);
    quicksort_v1(arr, x + 1, r);
    return;
}

/*
 * 单边递归法，将下一层右子树要做的交给本层来做
 * 通过修改l的值即可达到目的
 */
void quicksort_v2(int *arr, int l, int r)
{
    while(l < r)
    {
    // 下面开始partition操作，枢轴元素选取最左边
        int x = l, y = r, temp = arr[l];
        while(x < y)
        {
            while(x < y && arr[y] >= temp) --y;
            if(x < y) arr[x] = arr[y];
            while(x < y && arr[x] <= temp) ++x;
            if(x < y) arr[y] = arr[x];
        }
        arr[x] = temp;
        quicksort_v2(arr, l, x - 1);
        // quicksort_v1(arr, x + 1, r);
        l = x + 1;
    }
    return;
}

/*
 * 减少x < y的判断次数，这是一种编程思维
 * 将partition修改成少监督的方式
 * 为了说明这种方式，先以两个插排作为例子
 */

// 插排：从无序序列[l...r]中选一个放到有序序列中
void insertsort(int *arr, int l, int r)
{
    for(int i = l + 1; i <= r; ++i)
    {
        int j = i;
        while(j > l && arr[j] < arr[j - 1])
        {
            std::swap(arr[j], arr[j - 1]);
            --j;
        }
    }
    return;
}

#define my_swap(a, b) {\
    __typeof(a) __a = a;\
    a = b, b = __a;\
}

// 无监督插排：优化掉j > l判断
// 做一个预处理，将序列中最小的数放在第一个位置，就不需要做该判断
void unguarded_insertsort(int *arr, int l, int r)
{
    int ind = l;
    for(int i = l + 1; i <= r; ++i)
    {
        if(arr[i] < arr[ind]) ind = i;
    }
    while(ind > l)
    {
        std::swap(arr[ind], arr[ind - 1]);
        --ind;
    }
    for(int i = l + 2; i <= r; ++i)
    {
        int j = i;
        while(j > l && arr[j] < arr[j - 1])
        {
            std::swap(arr[j], arr[j - 1]);
            --j;
        }
    }
    return;
}

/*
 * 修改快排为无监督的方式(减少x < y的判断次数)
 */
void quicksort_v3(int *arr, int l, int r)
{
    while (l < r)
    {
        int x = l, y = r, z = arr[l];
        // partition，修改成无监督的方式（即减少x<y判断，这是一种编程思维
        // 即两侧指针同时向中间移动，do whle循环
        do
        {
            while (arr[x] < z) ++x;
            while (arr[y] > z) --y;
            if (x <= y)
            {
                std::swap(arr[x], arr[y]);
                ++x, --y;
            }
        } while(x <= y);
        quicksort_v3(arr, l, y);
        l = x;
    }
    return;
}

/*
 * 如果快排每一次选择的基准值都能将左右两块区间平分
 * 那么快排会达到最优的时间复杂度，会使得递归树高度较低
 * 最坏时间复杂度：每次Partition完后基准值都在两端（如有序序列）
 * 快速排序基准值选择优化
 * v4是基准值优化，每次随机选取作为枢轴
 */
void quicksort_v4(int *arr, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = arr[l + rand() % (r - l + 1)];
        // partition
        do
        {
            while (arr[x] < z) ++x;
            while (arr[y] > z) --y;
            if (x <= y)
            {
                std::swap(arr[x], arr[y]);
                ++x, --y;
            }
        } while(x <= y);
        quicksort_v4(arr, l, y);
        l = x;
    }
    return;
}

/*
 * v5：STL中quicksort实现方法，三点取中法
 * 每次选择l, mid, r三个数的中间数作为枢轴元素
 */
int median(int *arr, int l, int r) 
{
    int a = arr[l], b = arr[r], c = arr[(l + r) >> 1];
    if (a > b) my_swap(a, b);
    if (a > c) my_swap(a, c);
    if (b > c) my_swap(b, c);
    return b;
}

void quicksort_v5(int *arr, int l, int r) 
{
    while (l < r) 
    {
        int x = l, y = r, z = median(arr, l, r);
        // partition
        do
        {
            while (arr[x] < z) ++x;
            while (arr[y] > z) --y;
            if (x <= y)
            {
                my_swap(arr[x], arr[y]);
                ++x, --y;
            }
        } while(x <= y);
        quicksort_v5(arr, l, y);
        l = x;
    }
    return ;
}

/*
 * v6：混合排序方法
 * 数据量较多时选择快速排序，较少时选择无监督的插入排序
 */
void quicksort_v6(int *arr, int l, int r) {
    while(r - l > 16)
    {
        while (l < r)
        {
            int x = l, y = r, z = median(arr, l, r);
            // partition
            do
            {
                while (arr[x] < z) ++x;
                while (arr[y] > z) --y;
                if (x <= y) 
                {
                    my_swap(arr[x], arr[y]);
                    ++x, --y;
                }
            } while(x <= y);
            quicksort_v6(arr, l, y);
            l = x;
        }
    }
    if(l < r) unguarded_insertsort(arr, l, r);
    return ;
}