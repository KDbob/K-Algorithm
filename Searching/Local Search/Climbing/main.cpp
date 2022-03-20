// 8皇后问题的局部搜索
// Created by kaide on 2020/12/4.
//

#include <iostream>
#include <vector>

using namespace std;

class Queen {
    friend void nQueen(int n);
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
    p[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int k = rand() % n + 1;
        printf("%d", k);
        p[i] = k;
    }
    printf("\n");
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
 * 最陡爬山法（n皇后），每次循环只移动一步。
 */
bool Queen::Random_restart_Hill_Climbing() {
    // current ← problem.INITIAL-STATE
    //  Loop:
    //  neighbor ← a highest-valued successor of current  状态评估值最小
    //  if VALUE(neighbour) ≤ VALUE(current) then return current
    //  current ← neighbor

    RandomGenerate();  // 初始化棋盘
    vector<int> curr_state = GetState();
    vector<int> next_state;
    vector<int> best_state;

    int min_h = Conflict(curr_state);
    int new_h{};
    if (Conflict(curr_state) == 0) {
        printf("一开始就是最佳位置\n");
        return true;
    }

    while (true) {  // 遍历这个棋盘的所有下个状态（移动一个棋子）
        bool local_max_flag = true;
        for (int i = 1; i <= n; ++i) {   // 遍历列
            for (int j = 1; j <= n; ++j) {   // 遍历行
                if (curr_state[i] != j) {  // 如果不是初始摆放的那一行
                    next_state = curr_state;
                    next_state[i] = j;
                    new_h = Conflict(next_state);    // 计算下一步的代价值
                    if (new_h < min_h) {
                        local_max_flag = false;
                        // 状态评估值最小的状态记录一下，下次外循环的时候作为初始棋盘。
                        best_state = next_state;
                        min_h = new_h;
                        if (new_h == 0) {
                            printf("找到了皇后的位置\n");
                            return true;
                        }
                    }
                }
            }
        }
        if (local_max_flag) {
            printf("每所有的移动尝试都没有更好的值\n");
            return false;
        }
        curr_state = best_state;
    }
}

/*
* 跑n皇后
*/
void nQueen(int n) {
    Queen Q{};
    Q.n = n;
    Q.Steepest_Hill_Climbing();
}

int main() {
    srand(time(0));
    nQueen(8);
}