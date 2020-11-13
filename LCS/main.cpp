//
//  main.cpp
//  LCS
//  最长公共子序列问题
//  Created by kaide on 2020/11/12.
//  Copyright © 2020 kaide. All rights reserved.
//

#include <iostream>
#include "string"
using namespace std;

#define COL_MAX 5

/*!
 * @brief 生成C矩阵和S矩阵。
 *        C矩阵：存储Xi和Yi序列的LSCLength。
 *        S矩阵：记录 c[i][j] 的值是由哪一个子问题的解得到的
 * @param x 字符串x
 * @param y 字符串y
 * @param m 字符串x的长度
 * @param n 字符串y的长度
 * @param c C矩阵的引用
 * @param s B矩阵的引用
 */
void LCSLength(string x, string y, int m, int n, int c[][COL_MAX], int s[][COL_MAX]) {
    for (int i = 0; i <= m; ++i) c[i][0] = 0;
    for (int j = 0; j <= n; ++j) c[0][j] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                s[i][j] = 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                s[i][j] = 2;
            } else {
                c[i][j] = c[i][j - 1];
                s[i][j] = 3;
            }
        }
    }
}

/*!
 * @brief 打印数组
 * @param arr 数组的引用
 * @param row 数组的行数
 * @param col 数组的列数
 */
void Print(int arr[][COL_MAX], int row, int col) {
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/*!
 * @brief 得到两个字符串的最长公共序列
 * @param i x字符串最后一个字符的下标
 * @param j y字符串最后一个字符的下标
 * @param x x字符串
 * @param s 记录 c[i][j] 的值是由哪一个子问题的解得到的
 */
void LCS(int i, int j, string x, int s[][COL_MAX]) {
    if (i == 0 || j == 0) return;
    if (s[i][j] == 1) {
        LCS(i - 1, j - 1, x, s);
        cout << x[i];
    } else if (s[i][j] == 2) {
        LCS(i - 1, j, x, s);
    } else {
        LCS(i, j - 1, x, s);
    }
}

/*!
 * [改进]不使用数组S，而是利用数组C中的信息（自顶向下）反推出求解线路
 * @param i x字符串最后一个下标
 * @param j y字符串最后一个下标
 * @param x 字符串x
 * @param y 字符串y
 * @param c C矩阵：存储Xi和Yi序列的LSCLength。
 */
void LCS2(int i, int j, string x, string y, int c[][COL_MAX]) {
    if (i == 0 || j == 0) return;
    if (x[i] == y[j]) {
        LCS2(i-1, j-1, x, y, c);
        cout << x[i];
    } else if (c[i][j] == c[i - 1][j]) { // 由子问题2得来
        LCS2(i - 1, j, x, y, c);
    } else { // 由子问题3得来
        LCS2(i, j - 1, x, y, c);
    }
}

/*!
 * [改进]求两个字符串最长公共子序列的长度，并生成C矩阵（只用于求最长公共子序列的长度）
 *        C矩阵：存储Xi和Yi序列的LSCLength的最后两行
 * @param x 字符串x
 * @param y 字符串y
 * @param m 字符串x的长度
 * @param n 字符串y的长度
 * @param c C矩阵的引用
 * @return 最长公共子序列的长度
 */
int LCSLength2(string x, string y, int m, int n, int c[2][COL_MAX]) {
    for (int i = 0; i <= 1; ++i) c[i][0] = 0;
    for (int j = 0; j <= n; ++j) c[0][j] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i] == y[j]) {
                c[i%2][j] = c[(i-1)%2][j-1] + 1;    // 由于每个c[i][j]只参考了c[i-1][j-1]、c[i-1][j]、c[i][j-1]这三个cell的值
            } else if (c[(i-1)%2][j] > c[i%2][j-1]) {
                c[i%2][j] = c[(i-1)%2][j];
            } else {
                c[i%2][j] = c[i%2][j-1];
            }
        }
    }
    return c[1][n];
}


int main() {
    string X = " abcde";
    string Y = " abdf";
    int m = 5;
    int n = 4;
    int C[5+1][COL_MAX] = {0};
    int S[5+1][COL_MAX] = {0};
    LCSLength(X, Y, m, n, C, S);
    printf("打印C数组：\n");
    Print(C, m+1, n+1);
    printf("打印S数组：\n");
    Print(S, m+1, n+1);
    cout << "打印最长公共子序列：";
    LCS(m, n, X, S);
    cout << endl;

    // 改进1：不借助S矩阵，打印最长公共子序列
    cout << "不借助S矩阵，打印最长公共子序列：";
    LCS2(m, n, X, Y, C);
    cout << endl;

    // 改进2：用两行的数组C求出最长公共子序列的长度
    int C2[2][COL_MAX] = {0};
    printf("最长公共子序列的长度：%d\n", LCSLength2(X, Y, m, n, C2));
    cout << "只用两行的C数组：" << endl;
    Print(C2, 2, n);
}
