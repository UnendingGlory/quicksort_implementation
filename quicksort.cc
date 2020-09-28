/*
 * 最简单的快速排序版本，patition + 递归
 */
void quicksort_v1(int *arr, int l, int r)
{
    if(l >= r) return;
    // 下面开始patition操作，枢轴元素选取最左边
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