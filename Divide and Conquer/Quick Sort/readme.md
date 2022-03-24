# 快速排序

> 也是基于分治策略的一个排序算法。

## 基本思想

1. 分解( Divide )

   - 以a[p]为基准将元素将a[p:r]划分成3段：a[p:q-1]、a[q]、a[q+1:r]
     
     > 其中a[p:q-1]中的任意元素小雨等于a[q]，a[q+1:r]中的任意与萨努大于等于a[q]
   
2. 递归求解（Conquer）

   - 通过递归调用快速排序算法分别对a[p:q-1]和a[q+1:r]进行排序

3. 合并（Merge）

   - **不需要执行任何计算**，a[p:r]就已排好序。

**快速排序代码实现QuickSort**

```c
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

```



## 关键子算法

#### partition

以a [p] 为基准元素将a [p : r] 划分成3 段a [p: q - 1]，经过Partition一定能确定一个元素的最终位置，有两种实现方法

- **前后指针**

```c
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
```

- 快慢指针

```c
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
```

