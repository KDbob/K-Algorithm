//
//  main.cpp
//  Merge Sort
//
//  Created by kaide on 2020/10/26.
//  Copyright © 2020 kaide. All rights reserved.
//

#include <iostream>

using namespace std;

/**
 * 合并两个有序的子数组( A[p]~A[q]及A[q+l]~A[r]已按递增顺序排序 )
 * @param A 整数数组
 * @param p 第一个子数组的起始下标
 * @param q 第一个子数组的末尾下标
 * @param r 第二个字数组的末尾下标
 * @param n A数组的元素个数
 */
void merge(int A[], int p, int q, int r, int n) {
    int *B = new int[n];        // 建立缓冲区
    int k = 0;                  // 指向B的游标，主要用于插入数据进B中
    int i = p, j = q + 1;
    while (i <= q && j <= r) {                  // while循环的跳出条件是：i和j只要有一个超过各种数组的界限
        if (A[i] >= A[j]) {
            B[k++] = A[j++];
        } else {
            B[k++] = A[i++];
        }
    }
    if (i == q+1) {    // 说明是前半段先遍历完，把后半段的拼到数组后面
        while (j <= r) {
            B[k++] = A[j++];
        }
    } else {
        while (i <= q) {
            B[k++] = A[i++];
        }
    }
    // 将选定的部分替换为B的数组
    k = 0;
    for (i = p; i <= r; i++) {
        A[i] = B[k++];
    }
    delete[] B;
}

/**
 * 合并排序算法
 * @param A 乱序数组A
 * @param n 数组A的元素个数
 */
void merge_sort(int A[], int n) {
    int i,s;  // i: 开始合并时第一个序列的起始位置，s：合并前序列的大小，t：合并后序列的大小
    int t = 1;
    while (t < n) {  // 外层循环：合并的大趟数
        s = t;
        t *=2;
        i = 0;
        while (i + t < n) { // 内层循环：每趟需要合并的次数
            merge(A, i, i+s-1, i+s*2-1, t); // 💡难点：填写变量的参数
            i = i + t;
        }
        if (i + s < n) {  // 💡难点：判断还有剩下的元素待处理。
            merge(A, i, i+s-1, n-1, n-i);
        }
    }
}

/**
 从数组中，每5个元素为一组，取第i组的中值元素于数组p
 */
void mid(int A[], int i, int p[]){
    int k = 5 * i;
    if (A[k] > A[k+2]) {
        swap(A[k+2], A[k]);
    }
    if (A[k+1] > A[k+3]) {
        swap(A[k+3], A[k+1]);
    }
    if (A[k] > A[k+1]) {
        swap(A[k], A[k+1]);
    }
    if (A[k+2] > A[k+3]) {
        swap(A[k+2], A[k+3]);
    }
    if (A[k+1] > A[k+2]) {
        swap(A[k+1], A[k+2]);
    }
    if (A[k+4] > A[k+2]) {
        p[i] = A[k+2];
    } else if (A[k+4] > A[k+1]) {
        p[i] = A[k+4];
    } else {
        p[i] = A[k+1];
    }
}

/**
    选择算法
    输入：n个元素的数组A[]，所要选择的第k小的元素
    输出：所选择的元素
 */
int select(int A[], int n, int k) {
    int i, p, q, r;
    int m, *P, *Q, *R;
    if (n <= 3) {   // 元素个数小于阀值，直接排序
        merge_sort(A, n);
        return A[k - 1];    // 返回第k小元素
    }
    // 把原数组划分成P,Q,R三组，使得小于m的元素存放于P，等于m的元素存放于Q，大于m的元素存放于R
    P = new int[3*n/4];     // 通过数学计算得到的：数组规模最大也只有以前的3/4
    Q = new int[3*n/4];
    R = new int[3*n/4];
    for (i=0; i<n/5; i++) { // 把每组5个元素的中值元素依次存于P
        mid(A, i, P);
    }
    
    m = select(P, i, i/2+i%2);  // 递归第调用，取得中值元素的中值元素：m（巧妙点：这个函数也能返回中值）
    p = q = r = 0;
    for (int i=0; i<n; i++) {
        if (A[i] < m) {
            P[p++] = A[i];
        } else if (A[i] > m) {
            R[r++] = A[i];
        } else {
            Q[q++] = A[i];
        }
    }
    // 2.划分成子问题
    if (p > k) {  // 第k小的元素在数组P中，继续在P中进行寻找。
        return select(P, p, k);
    } else if (p+q >= k) { // 第k小的元素在Q中，直接返回m
        return m;
    } else {    // 第k小的元素在R中，在R中继续寻找
        return select(R, r, k-p-q);
    }
}

void test_select(){
    int a[] = {8,31,60,33,17,4,51,57,49,35,11,43,37,3,13,52,6,19,25,32,54,16,5,41,7,23,22,46,29};
    int k = select(a, 29, 18);
    printf("%d", k);
}

/**
 * 合并排序的递归实现（分治法）
 * @param A 乱序的数组A
 * @param low 数组的起始下标
 * @param high 数组的末尾下标
 */
void merge_sort(int A[], int low, int high) {
    if (low < high) {   // 说明至少还存在两个元素：需要进行分
        int i = (low + high) / 2;       // 获得中间位置的下标(偏左)
        merge_sort(A, low, i);          // 分操作：对左半部分的子序列递归调用
        merge_sort(A, i+1, high);   // 分操作：对右半部分的子序列递归调用
        merge(A, low, i, high, high-low+1); // 治操作：解决有序两个子序列的合并
    }
}

int main() {
    int a[] = {8, 5, 3, 9, 11, 6, 4, 1, 10, 7, 2, 11};
    merge_sort(a, 0, 10);   // 归并排序的非递归实现
    for (int i=0;i < 11; i++) {
        printf("%d ",a[i]);
    }
    // 1 2 3 4 5 6 7 8 9 10 11
}


void test() {
    // insert code here...
        int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
        merge(a, 0, 4, 9, 10);
        // 测试两个元素的数组
//        int a2[] = {6, 2};
//        merge(a2, 0, 0, 1, 2);
//        int a[] = {8,7,6,5,4,3,2,1};
        merge_sort(a, 8);

//        merge(a, 0, 0, 1, 2);
//        merge(a, 2, 2, 3, 2);
        // 测试mide
    //    int a[] = {1,2,3,5,4};
    //    int *p = new int(2);
    //    mid(a, 0, p);

}
