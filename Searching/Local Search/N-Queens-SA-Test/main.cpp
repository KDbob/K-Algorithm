#include<iostream>
#include<string.h>
#include<time.h>
using namespace std;

#define MAX_SIZE 10000  //最大可求解的皇后数量

int n;  //待输入的皇后数量
int board[MAX_SIZE];  //记录棋盘状况的数组
int board_new[MAX_SIZE];   //临时状况数组
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
int Conflict(int *array) {
    int i, j, r = 0;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++) {
            if (j - i == abs(array[j] - array[i])||array[i] == array[j])
                r++;
        }
    return 28 - r;
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

/**
 * 将arr1的内容复制给arr2
 */
void CopyArray(int *arr1, int *arr2) {
    for (int i = 0; i < n; ++i) {
        arr1[i] = arr2[i];
    }
}

bool Simulated_Annealing(int n){
   int steps = 0;
   double T = 100;    // 初始温度
   RandArray(n);

   int old_value = 0;
   int new_value = 0;

   while (T > 1) {
       ++steps;
       T *= 0.9;   //降温
       old_value = Conflict(board);
       if (old_value == 0) {
           printf("成功找到\n");
           return true;
       }
       // 随机选择一个新的邻接状态
       int y = rand() % 8;
       int x = 0;
       while (1) {
           x = rand() % 8;
           if (x != board[y] - '0') break;
       }
       CopyArray(board_new, board);
       board_new[y] = x;

       new_value = Conflict(board_new);
       int deltaE = (new_value - old_value);
       if (deltaE > 0) {                            // 如果新的评估值更优
           printf("是更优解，接受\n");
           CopyArray(board, board_new);
       } else {
            cout << deltaE << ": " << T << ":" << deltaE / T << " : " << exp(deltaE / T) << endl;
           // 如果新的评估值差于旧的评估值，则有小概率采纳新的较差的评估值对应的新状态，允许下山
           if (((float) (rand() % 1000) / 1000) < exp(deltaE / T)) {
               printf("结果较差，但也被接受\n");
               CopyArray(board, board_new);
           } else {    // 较差的新状态被否决，时间越长，较差的新状态越容易被否决
               printf("被拒绝\n");
           }
       }
   }
    return false;
}

int main() {
    srand((unsigned) time(NULL));
    int t1, t2;
    cout << "\n输入棋盘大小(皇后个数)：";
    cin >> n;
    cout << endl;
    t1 = clock();   // 计时开始

    Simulated_Annealing(n);  // 本地搜索

    t2 = clock();   // 计时结束
//    PrintBoard();
    cout << " 耗费时间：" << (t2 - t1)/CLOCKS_PER_SEC << " s\n";
    return 0;
}