//
// Created by kaide on 2020/12/28.
//

#include <iostream>
#include <vector>

using namespace std;

class Queen {
    friend bool nQueen(int n);

private:
    int n; // 皇后的个数
    int *board; // 棋盘
    vector<int> state;  // 棋盘当前状态
public:
    void RandomGenerate(); // 初始化棋盘
    // 获取棋盘的序列
    vector<int> GetState() {
        vector<int> list;
        list.reserve(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            list.push_back(*(board + i));
        }
        return list;
    }

    int Conflict(vector<int> state_);   // 冲突数
    bool Random_restart_Hill_Climbing();  // 最陡爬山算法
};

// 初始化棋盘
void Queen::RandomGenerate() {
    int *p = new int[n + 1];
    int *label = new int[n + 1];  //标记数组
    p[0] = 0;
    int i, temp;
    for (i = 1; i <= n; i++) {
        do {
            temp = rand() % n + 1;
        } while (label[temp] == 1);
        p[i] = temp;
        label[temp] = 1;
    }
    board = p;
}

// 冲突数
int Queen::Conflict(vector<int> state_) {
    int i, j, r = 0;
    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++) {
            if (j - i == abs(state_[j] - state_[i]) || state_[j] == state_[i])
                r++;
        }
    return r;
}

/*
 * 随机重启爬山法（n皇后），每次循环交换一列。
 */
bool Queen::Random_restart_Hill_Climbing() {
    vector<int> curr_state, next_state, best_state;
    int min_h{}, new_h{};

    while (true){  // 5.如果陷入了局部极小，即交换了所有皇后后，冲突仍不能下降
        RandomGenerate();  //1. 随机地将N个皇后分布在棋盘上，使得棋盘的每行、每列只有一个皇后
        curr_state = GetState();
        min_h = Conflict(curr_state);   // 2.计算皇后间的冲突数Conflicts

        if (min_h == 0) {   // 3. 如果冲突数等于0
            printf("一开始就是最佳位置\n");
            return true;
        }
        // 4.对于棋盘上的任意两个皇后，交换他们的位置，如果交换后的冲突数减少，则接受这种交换，更新h
        // 整个while循环只交换最好的那列
        while (true){
            bool trap_flag = true;
            for (int i = 1; i < n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    next_state = curr_state;
                    next_state[i] = curr_state[j];
                    next_state[j] = curr_state[i];
                    new_h = Conflict(next_state);
                    if (new_h < min_h) {
                        if (new_h == 0) {   // 3. 如果冲突数等于0
                            printf("找到了皇后的位置\n");
                            return true;
                        }
                        trap_flag = false;
                        best_state = next_state;
                        min_h = new_h;
                    }
                }
            }
            if (trap_flag) {
                printf("陷入了局部极小，即交换了所有皇后，冲突数仍不能下降\n");
                break;
            }
            curr_state = best_state;
        }
    };

}

/*
* 跑n皇后
*/
bool nQueen(int n) {
    Queen Q{};
    Q.n = n;
    Q.Random_restart_Hill_Climbing();
}


int main() {
    srand(time(0));
    nQueen(100);
}