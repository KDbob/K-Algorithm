//
//  main.cpp
//  MatrixChain
//  矩阵连乘问题
//  Created by kaide on 2020/10/30.
//  Copyright © 2020 kaide. All rights reserved.
//

#include <iostream>
#include "string"

using namespace std;
#define NUM 6

int p[NUM+1] = {30, 35, 15, 5, 10, 20, 25};
int n = 6;
int m[NUM+1][NUM+1];
int s[NUM+1][NUM+1];


/**
* @brief      计算出最优值：最少连乘次数矩阵：m，最少连乘括号位置矩阵：s
* @param p    记录矩阵的行列值（n个矩阵用n+1个值来表示）
* @param n    连乘矩阵个数
* @param m    矩阵连乘A[i:j]的开始值下标i
* @param s    矩阵连乘A[i:j]的结束值j
**/
void MatrixChain(int p[NUM+1], int n, int m[][NUM+1], int s[][NUM+1]) {
    for (int i=1; i<=n; i++) m[i][i] = 0;
    for (int r=2; r<=n; r++) {  // 按对角线方向递增
        for (int i=1; i<=n-r+1; i++) {
            int j = i + r - 1;
            m[i][j] = m[i+1][j] + p[i-1]*p[i]*p[j]; // m[i][j]的预设值为: A[i:i]和A[i+1:j]的连乘最小值
            s[i][j] = i;                            // s[i][j]的预设值为：i(即括号就在i后面)
            for (int k=i+1; k<j; k++) {     // 遍历A[i:k]xA[k+1:j]的连乘，其中括号的位置为k
                int temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (temp < m[i][j]) {   // m[i][j]取最优子结构的解
                    m[i][j] = temp;
                    s[i][j] = k;
                }
            }
        }
    }
}

void PrintMatrx(int k[][NUM+1], int row, int col) {
    for (int i=1; i<row; i++) {
        for (int j=1; j<col; j++) {
            printf("%5d ", k[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
* @brief      打印：矩阵连乘A[i:j]的加括号结果
* @param s    最少连乘括号位置矩阵s
* @param i    矩阵连乘A[i:j]的开始值下标i
* @param j    矩阵连乘A[i:j]的结束值j
*
* @return String     A[i:j]的加括号结果如：(A1(A2A3))((A4A5)A6)
*/
string Traceback(int i, int j, int s[][NUM+1]) {
    if (i == j) {
        string ret = "A";
        return ret + to_string(i);
    }
    string left = Traceback(i, s[i][j], s);    // 左半部分的括号划分
    string right = Traceback(s[i][j]+1, j, s);     // 右半部分的括号划分
    short leftLen = left.size();
    short rightLen = right.size();
    if (leftLen >= 4) {
        left = "(" + left + ")";
    }
    if (rightLen >= 4) {
        right = "(" + right + ")";
    }
    return left + right;
}

/**
* @brief [改进]通过最少连乘次数矩阵m所在的位置，反推出括号所在的位置
* @param m      最少连乘次数矩阵：m
* @param row    m矩阵某位置的行下标
* @param col    m矩阵某位置的列下标
*
* @return i     括号所在位置(在Ai的后面加括号)
*/
int GetLocal(int m[][NUM+1], int row, int col) {
    int i = row;
    int j = col;
    if (i == j) {
        return i;
    } else if (i < j) {
        int min = m[i][j];
        int local = i;  // 预设的位置为i
        for (int k=row+1; k<col; k++) {
            int temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
            // 判断min的值在哪个位置
            if (temp == min) {
                local = k;
            }
        }
        return local;
    } else {
        return 0;
    }
}

/**
* @brief      打印：矩阵连乘A[i:j]的加括号结果（[改进]通过GetBracketLocation动态地从m矩阵中获取括号位置）
* @param m    最少连乘次数矩阵m
* @param i    矩阵连乘A[i:j]的开始值下标i
* @param j    矩阵连乘A[i:j]的结束值j
*
* @return String     A[i:j]的加括号结果如：(A1(A2A3))((A4A5)A6)
*/
string Traceback2(int i, int j, int m[][NUM+1]) {
    if (i == j) {
        string ret = "A";
        return ret + to_string(i);
    }
    string left = Traceback2(i, GetLocal(m, i, j), m);    // 左半部分的括号划分
    string right = Traceback2(GetLocal(m, i, j)+1, j, m);     // 右半部分的括号划分
    short leftLen = left.size();
    short rightLen = right.size();
    if (leftLen >= 4) {
        left = "(" + left + ")";
    }
    if (rightLen >= 4) {
        right = "(" + right + ")";
    }
    return left + right;
}


/**
* @brief      A[1:n]矩阵连乘的方案数
* @param n    连乘的矩阵个数
*
* @return int 方案数
*/
int NumberOfPlan(int n) {
    if (n==1) {
        return 1;;
    } else {
        int sum = 0;
        for (int i=1; i<n; i++) {   // 1个一组，2个一组...直到n个一组来加括号一共执行n-1遍循环
            int temp = NumberOfPlan(i) * NumberOfPlan(n-i);   // 左边的方案数*右边的括号数
            sum +=temp;
        }
        return sum;
    }
}

int main(int argc, const char * argv[]) {
    // 1.计算最优值
    MatrixChain(p, NUM, m, s);
    // 打印最少连乘值矩阵：m
    PrintMatrx(m, NUM+1, NUM+1);
    // 打印最佳括号位置矩阵：s
    PrintMatrx(s, NUM+1, NUM+1);
    // 2.打印括号形式
    string result = Traceback(1, NUM, s);
//    cout << result << endl;
//    // 2.改进的打印括号形式(不用s矩阵)
//    string result2 = Traceback2(1, NUM, m);
//    cout << result2 << endl;
//    // 输出总共的方案数
    printf("矩阵连乘的方案数为：%d\n",NumberOfPlan(5));
    return 0;
}
