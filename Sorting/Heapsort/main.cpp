//
// Created by bob on 2022/5/2.
//
#include<vector>

using namespace std;

void maxHeapify(vector<int>& a, int i, int heapSize) {
    int l = i * 2;
    int r = i * 2 + 1;
    int largest = i;
    if (l < heapSize && a[l] > a[largest]) {
        largest = l;
    }
    if (r < heapSize && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, largest, heapSize);
    }
}

void buildMaxHeap(vector<int> &a, int heapSize) {
    for (int i = heapSize / 2; i > 0; --i) {
        maxHeapify(a, i, heapSize);
    }
}

int main(){
    vector<int> nums = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    buildMaxHeap(nums, 11); //expect：[0, 16, 14, 10, 8, 7, 9, 3, 2, 4, 1]
    return 0;
}