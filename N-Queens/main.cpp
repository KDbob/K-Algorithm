//
// Created by kaide on 2020/12/4.
//

#include <iostream>

using namespace std;

class Queen {
    friend int nQueen(int);
private:
    bool Place(int k);

    void Backtrack(int t);
    void IterativeBacktrack();
    int n; // 皇后个数
    int *x; // 当前解
    long sum; // 当前已找到的可行方案数
};

/**
 * 判断放置的皇后是否正确
 * @param k
 * @return
 */
bool Queen::Place(int k) {
    for (int j = 1; j < k; ++j) {
        if(abs(k-j)==abs(x[j]-x[k])||(x[j]==x[k]))
            return false;
    }
    return true;
}
/*
 * 递归回溯
 */
void Queen::Backtrack(int t) {
    if (t > n) {
        sum ++;
    } else {
        for (int i = 1; i <= n; ++i) {
            x[t] = i;
            if(Place(t)) {
                Backtrack(t+1);
            }
        }
    }
}
/*
 * 迭代回溯
 */
void Queen::IterativeBacktrack() {
    int t = 1;  // 递归深度
    x[1] = 0;   // 将第一列的放置棋子（行）初始化
    while (t > 0) {
        x[t] += 1;
        while ((x[t]<=n)&&!Place(t)) {  // 如果将要放置的行没有溢出，且不满足放置条件
            x[t] += 1;
        }
        if (x[t] <= n) {                // 如果这次放置的行满足条件
            if (t==n) sum++;            // 如果达到Solution条件，输出值
            else {
                t++;                    // 递归深度+1
                x[t] = 0;               // 将这次放置的不满足的棋子（行）初始化
            }
        } else {
            t--;                        // 递归深度-1
        }
    }
}

int nQueen(int n) {
    Queen X;
    X.n = n;
    X.sum = 0;
    int *p = new int[n + 1];
    for (int i = 0; i <= n; ++i) {
        p[i] = 0;
    }
    X.x = p;
//    X.Backtrack(1);   // 递归算法
    X.IterativeBacktrack();     // 迭代算法
    delete []p;
    return X.sum;
}

int main() {
    cout << nQueen(4) << endl;
}