#include<iostream>
#include<string.h>
#include<time.h>
using namespace std;

#define MAX_SIZE 10000  //最大可求解的皇后数量

int n = 8;  //待输入的皇后数量
int board[MAX_SIZE];  //记录棋盘状况的数组
int label[MAX_SIZE];  //标记数组

/**
 * 初始：随机摆放棋盘
 */
void RandArray(int x) {
    int i, temp;
    memset(label, 0, sizeof(int) * (n + 1));
    for (i = 0; i < n; i++) {
        do {
            temp = rand() % x;
        } while (label[temp] == 1);
        board[i] = temp;
        label[temp] = 1;
    }
}

/**
 * 使用暴力循环方法计算冲突
 * @return 冲突数
 */
int Conflict() {
    int i, j, r = 0;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++) {
            if (j - i == abs(board[j] - board[i]))
                r++;
        }
    return r;
}

void PrintBoard(){
    for (int i = 0; i < n; i++) {  //打印皇后在棋盘中的分布
        for (int j = 0; j < n; j++) {
            if (board[i] == j) cout << " X";
            else cout << " +";
        }
        cout << endl;
    }
}

void LocalSearch(){
    int now;
    while (1) {
        RandArray(n);   // 初始摆放
        now = Conflict();
        next:
        if (now == 0) {
            PrintBoard();
            goto over;
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {  //单步长
                int temp = board[i];
                board[i] = board[j];
                board[j] = temp;
                int fnow = Conflict();
                if (fnow < now) {
                    now = fnow;
                    goto next;
                }
                temp = board[i];
                board[i] = board[j];
                board[j] = temp;
            }
        }
    }
    over:
    return;
}

int test() {


}

int main() {
    srand((unsigned) time(NULL));
    int t1, t2;
    cout << "\n输入棋盘大小(皇后个数)：";
    cin >> n;
    cout << endl;
    t1 = clock();   // 计时开始

    LocalSearch();  // 本地搜索

    t2 = clock();   // 计时结束
//    PrintBoard();
    cout << " 耗费时间：" << (t2 - t1)/CLOCKS_PER_SEC << " s\n";
    return 0;
}