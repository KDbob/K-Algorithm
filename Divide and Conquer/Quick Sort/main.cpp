//
// Created by bob on 2022/3/22.
//
#include<iostream>
using namespace std;

/**
 * 以a [p] 为基准元素将a [p : r] 划分成3 段a [p: q - 1]
 * 《前后指针交换》
 * @param a 数组
 * @param p 起始位置
 * @param r 结束位置
 * @return q 基准元素最后的位置
 */
int Partition(int a[], int p, int r) {
    int i = p, j = r + 1;
    int x = a[p];
    while (true) {
        while (a[++i] < x && i < r);
        while (a[--j] > x);
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    a[p] = a[j];
    a[j] = x;
    return j;
}

/**
 * 以a [p] 为基准元素将a [p : r] 划分成3 段a [p: q - 1]，经过Partition一定能确定一个元素的最终位置
 * 《快慢指针》
 * @param a 数组
 * @param l 起始位置
 * @param r 结束位置
 * @return q 基准元素最后的位置
 */
int Partition2(int a[], int l, int r) {
    int x = a[r], i = l - 1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= x) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

/**
 * 快速排序
 * @param a 数组
 * @param p 排序的起始位置
 * @param r 排序的结束位置
 */
void QuickSort(int a[], int p, int r) {
    if (p < r) {
        int q = Partition(a, p, r);
        QuickSort(a, p, q - 1); // 对左半段排序
        QuickSort(a, q + 1, r); // 对右半段排序
    }
}



int main() {
    // 1.partition测试
    int a[] = {8, 5, 3, 9, 12, 6, 4, 1, 10, 7, 2, 11};
//    int q = Partition(a, 0, 11);
//    int q2 = Partition2(a, 0, 11);
    // 2.快速排序
    QuickSort(a, 0, 11);
    return 0;
}