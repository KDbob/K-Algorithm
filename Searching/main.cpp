#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>


using namespace::std;


/* Use Hill-Climbing, Simulated-Annealing and Genetic-Algorithm to solve 8-Queens problem */
int SHC_success_total_steps = 0;	// 最陡上升爬山法成功总步数
int SHC_failed_total_steps = 0;		// 最陡上升爬山法失败总步数
int FCHC_success_total_steps = 0;	// 首选爬山法成功总步数
int FCHC_failed_total_steps = 0;	// 首选爬山法失败总步数
int RRSHC_success_total_steps = 0;	// 随机重启爬山法成功总步数
int RRSHC_failed_total_steps = 0;	// 随机重启爬山法失败总步数
int SA_success_total_steps = 0;		// 模拟退火成功总步数
int SA_failed_total_steps = 0;		// 模拟退火失败总步数
int generation = 0;					// 遗传算法成功所需总代数

class Board {
private:
    bool board[8][8];	// 棋盘
    int state[8];		// 状态的 8 位数串
public:
    int h_value_board[8][8] = {};   // 辅助的数据成员，表示8*8棋盘上的所有下一步状态的评估值

    /**
     * 内部先调用了一次 initial()，然后根据 state 数据成员往棋盘 board 放入 8 个皇后
     */
    void fill_in_board() {
        initial();
        for (int i = 0; i < 8; ++i) {
            board[state[i]][i] = true;
        }
    }

    void initial() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = false;
            }
        }
    }

    void random_initial_state() {
        for (int i = 0; i < 8; ++i) {
            state[i] = rand() % 8;
        }
    }

    void display(int mode) {
        cout << endl << "-------------------------------------" << endl;
        cout << "State: " << get_state() << endl
             << "h: " << (mode == 0 ? h_of_attack_pair() : h_of_not_attack_pair()) << endl
             << "Find Solution: " << (check(mode) ? "Success!!!" : "Failed...") << endl
             << "Board: " << endl;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "-------------------------------------" << endl;

    }

    void display_h_value_on_board() {
        cout << "H_Value On Board: " << endl;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << h_value_board[i][j] << " ";
            }
            cout << endl;
        }
    }

    void set_state(string state_) {
        for (int i = 0; i < 8; ++i) {
            state[i] = state_[i] - '0';
        }
    }

    string get_state() {
        string res;
        for (int i = 0; i < 8; ++i) {
            res += state[i] + '0';
        }
        return res;
    }

    bool check(int mode) {
        if (mode == 0) return h_of_attack_pair() == 0;
        else return h_of_not_attack_pair() == 28;
    }

    /**
     * 启发式评估函数 —— 相互攻击的皇后的数量。
     */
    int h_of_attack_pair() {
        int value = 0;
        for (int i = 0; i < 8; ++i) {
            value += count_attack(state[i], i);
        }
        return value / 2;
    }

    /*
     * 启发式评估函数 —— 不相互攻击的皇后的数量。
     */
    int h_of_not_attack_pair() {
        int value = 0;
        for (int i = 0; i < 8; ++i) {
            value += (7 - count_attack(state[i], i));
        }
        return value / 2;
    }

    int count_attack(int x, int y) {
        int count = 0;
        // 行
        for (int i = 0; i < 8; ++i) {
            if (i != y && board[x][i]) {
                count++;
            }
        }

        // 左上
        for (int i = x, j = y; i > 0 && j > 0; ) {
            if (board[--i][--j]) count++;
        }

        // 右下
        for (int i = x, j = y; i < 7 && j < 7; ) {
            if (board[++i][++j]) count++;
        }

        // 右上
        for (int i = x, j = y; i > 0 && j < 7; ) {
            if (board[--i][++j]) count++;
        }

        // 左下
        for (int i = x, j = y; i < 7 && j > 0; ) {
            if (board[++i][--j]) count++;
        }

        return count;
    }

};

Board b_tool;

// HILL-CLIMBING
bool Steepest_Hill_Climbing(Board* board) {

    int steps = 0;
    string old_state = board->get_state();
    string new_state = old_state;
    string best_state = old_state;
    int min_h = board->h_of_attack_pair();
    int new_h;

    while (1) {
        ++steps;
        bool local_max_flag = true;     // 局部最大值flag
        // 对于 i 列
        for (int i = 0; i < 8; ++i) {
            // 将 i 列中的皇后尝试其他的可能性
            for (int j = 0; j < 8; ++j) {
                if (old_state[i] != j + '0') {

                    new_state = old_state;
                    new_state[i] = j + '0';

                    board->set_state(new_state);
                    board->fill_in_board();
                    new_h = board->h_of_attack_pair();

//                    board->h_value_board[j][i] = new_h;

                    if (new_h < min_h) {
                        min_h = new_h;
                        best_state = new_state;
                        local_max_flag = false;
                        if (min_h == 0) {
                            SHC_success_total_steps += steps;
                            return true;
                        }
                    }
                }
//                else board->h_value_board[j][i] = 0;
            }
        }

        board->set_state(best_state);
        board->fill_in_board();
        // board->display();
        // board->display_h_value_on_board();

        if (local_max_flag) {
            // cout << "Attain local max: break the hill-climbing" << endl;
            SHC_failed_total_steps += steps;
            return false;
        }

        old_state = best_state;

    }

}

bool First_Choice_Hill_Climbing(Board* board) {

    int steps = 0;
    string old_state = board->get_state();
    string new_state = old_state;
    string best_state = old_state;
    int min_h = board->h_of_attack_pair();
    int new_h;

    while (1) {
        ++steps;
        bool find_flag = false;
        // 对于 i 列
        for (int i = 0; i < 8; ++i) {
            // 将 i 列中的皇后尝试其他的可能性
            for (int j = 0; j < 8; ++j) {
                if (old_state[i] != j + '0') {

                    new_state = old_state;
                    new_state[i] = j + '0';

                    board->set_state(new_state);
                    board->fill_in_board();
                    new_h = board->h_of_attack_pair();

                    board->h_value_board[j][i] = new_h;

                    if (new_h < min_h) {
                        min_h = new_h;
                        best_state = new_state;
                        find_flag = true;
                        if (min_h == 0) {
                            FCHC_success_total_steps += steps;
                            return true;
                        }
                        break;
                    }
                }
                else board->h_value_board[j][i] = 0;
            }
            if (find_flag) break;
        }

        board->set_state(best_state);
        board->fill_in_board();
        // board->display();
        // board->display_h_value_on_board();

        if (!find_flag) {
            // cout << "Attain local max: break the hill-climbing" << endl;
            FCHC_failed_total_steps += steps;
            return false;
        }

        old_state = best_state;

    }

}

bool Random_Restart_Steepest_Hill_Climbing(Board* board) {
    // 随机重启 1000 次
    for (int i = 0; i < 50; ++i) {
        if (!Steepest_Hill_Climbing(board)) {
            board->random_initial_state();
            board->fill_in_board();
        }
        else {
            RRSHC_success_total_steps += (SHC_failed_total_steps + SHC_success_total_steps);
            SHC_success_total_steps = 0;
            SHC_failed_total_steps = 0;
            return true;
        }

    }
    RRSHC_failed_total_steps += (SHC_failed_total_steps + SHC_success_total_steps);
    SHC_success_total_steps = 0;
    SHC_failed_total_steps = 0;
    return false;
}


void SHC_test1() {
    Board board;

    cout << "For the first cases: " << endl;
    board.initial();
//    board.set_state("16471352");
    board.random_initial_state();
    board.fill_in_board();
    board.display(0);
    Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
        cout << "Success_steps :" + to_string(SHC_success_total_steps) << endl;
    }
    else {
        cout << "Failed" << endl;
        cout << "Failed_steps :" + to_string(SHC_failed_total_steps) << endl;
    }

    board.display(0);

    cout << endl;

    cout << "For the second cases: " << endl;
//    board.set_state("45634565");
    board.random_initial_state();
    board.fill_in_board();
    board.display(0);
    Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);

    cout << endl;

    cout << "For the third cases: " << endl;
    board.random_initial_state();
    board.fill_in_board();
    board.display(0);
    Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);
}

void SHC_test2() {

    Board board;
    int count = 0;


    for (int i = 0; i < 1000; ++i) {
        board.initial();
        board.random_initial_state();
        board.fill_in_board();
        cout << board.get_state() << endl;
        Steepest_Hill_Climbing(&board);
        if (board.check(0)) {
            ++count;
        }
    }
    cout << "Random_restart_Hill_Climbing: " << endl
         << "Success Rate: " << float(count) / 1000 << " [" << count << "/1000]" << endl
         << "Success average steps: " << float(SHC_success_total_steps) / count << endl
         << "Failed average steps: " << float(SHC_failed_total_steps) / (1000 - count) << endl;

}

void FCHC_test1() {
    Board board;

    cout << "For the first cases: " << endl;
    board.initial();
    board.set_state("16471352");
    board.fill_in_board();
    board.display(0);
    First_Choice_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);

    cout << endl;

    cout << "For the second cases: " << endl;
    board.set_state("45634565");
    board.fill_in_board();
    board.display(0);
    First_Choice_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);

    cout << endl;

    cout << "For the third cases: " << endl;
    board.random_initial_state();
    board.fill_in_board();
    board.display(0);
    First_Choice_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);
}

void FCHC_test2() {

    Board board;
    int count = 0;

    for (int i = 0; i < 1000; ++i) {
        board.initial();
        board.random_initial_state();
        board.fill_in_board();
        cout << board.get_state() << endl;
        First_Choice_Hill_Climbing(&board);
        if (board.check(0)) ++count;
    }

    cout << "First_Choice_Hill_Climbing: " << endl
         << "Success Rate: " << float(count) / 1000 << " [" << count << "/1000]" << endl
         << "Success average steps: " << float(FCHC_success_total_steps) / count << endl
         << "Failed average steps: " << float(FCHC_failed_total_steps) / (1000 - count) << endl;
}

void RRSHC_test1() {

    Board board;

    cout << "For the first cases: " << endl;
    board.initial();
    board.set_state("16471352");
    board.fill_in_board();
    board.display(0);
    Random_Restart_Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);

    cout << endl;

    cout << "For the second cases: " << endl;
    board.set_state("45634565");
    board.fill_in_board();
    board.display(0);
    Random_Restart_Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);

    cout << endl;

    cout << "For the third cases: " << endl;
    board.random_initial_state();
    board.fill_in_board();
    board.display(0);
    Random_Restart_Steepest_Hill_Climbing(&board);
    if (board.check(0)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(0);
}

void RRSHC_test2() {
    Board board;
    int count = 0;

    for (int i = 0; i < 1000; ++i) {
        board.initial();
        board.random_initial_state();
        board.fill_in_board();
        cout << board.get_state() << endl;
        Random_Restart_Steepest_Hill_Climbing(&board);
        if (board.check(0)) ++count;
    }

    cout << "Random_Start_Steepest_Hill_Climbing: " << endl
         << "Success Rate: " << float(count) / 1000 << " [" << count << "/1000]" << endl
         << "Success average steps: " << float(RRSHC_success_total_steps) / count << endl;
    cout << "Failed average steps: ";
    if (1000 - count == 0) cout << "never failed" << endl;
    else cout << float(RRSHC_failed_total_steps) / (1000 - count) << endl;
}

float schedule(float T) {
    return 0.9999 * T;
}

// SIMULATED-ANNEALING
bool Simulated_Annealing(Board* board, float(*p)(float)) {
    int steps = 0;
    double T = 5;		// 把初始温度设置为 5
    string old_state = board->get_state();
    string new_state = old_state;
    int old_value = 0;
    int new_value = 0;

    while (T > 0.00001) {
        ++steps;
        old_value = board->h_of_not_attack_pair();
        if (board->check(1)) {
            SA_success_total_steps += steps;
            return true;
        }
        T = (*p)(T);

        // 随机选择一个新的邻接状态
        // 随机抽取一个列
        int y = rand() % 8;
        int x = 0;
        // 随机抽取该列中的 free 的行（也即没有皇后的行）
        while (1) {
            x = rand() % 8;
            if (x != old_state[y] - '0') break;
        }
        new_state = old_state;
        new_state[y] = x + '0';

        board->set_state(new_state);
        board->fill_in_board();
        new_value = board->h_of_not_attack_pair();
        int deltaE = (new_value - old_value);

        if (deltaE > 0) {
            old_state = new_state;
        }
        else {
            // cout << deltaE << ": " << T << ":" << deltaE / T << " : " << exp(deltaE / T) << endl;

            if (((float)(rand() % 1000) / 1000) < exp(deltaE / T)) {
                old_state = new_state;
            }
            else {
                board->set_state(old_state);
                board->fill_in_board();
            }
        }
    }

    SA_failed_total_steps += steps;
    return false;
}

void SA_test1() {
    Board board;

    cout << "For the first cases: " << endl;
    board.initial();
    board.set_state("16471352");
    board.fill_in_board();
    board.display(1);
    Simulated_Annealing(&board, &schedule);
    if (board.check(1)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(1);

    cout << endl;

    cout << "For the second cases: " << endl;
    board.set_state("45634565");
    board.fill_in_board();
    board.display(1);
    Simulated_Annealing(&board, &schedule);
    if (board.check(1)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(1);

    cout << endl;

    cout << "For the third cases: " << endl;
    board.random_initial_state();
    board.fill_in_board();
    board.display(1);
    Simulated_Annealing(&board, &schedule);
    if (board.check(1)) {
        cout << "Success" << endl;
    }
    else cout << "Failed" << endl;
    board.display(1);
}

void SA_test2() {

    Board board;
    int count = 0;


    for (int i = 0; i < 1000; ++i) {
        board.initial();
        board.random_initial_state();
        board.fill_in_board();
        cout << i << " : " << board.get_state() << endl;
        Simulated_Annealing(&board, schedule);
        if (board.check(1)) ++count;
    }

    cout << "Simulated_Annealing_Hill_Climbing: " << endl
         << "Success Rate: " << float(count) / 1000 << " [" << count << "/1000]" << endl
         << "Success average steps: " << float(SA_success_total_steps) / count << endl;
    cout << "Failed average steps: ";
    if (1000 - count == 0) cout << "never failed" << endl;
    else cout << float(SA_failed_total_steps) / (1000 - count) << endl;
}


// GENETIC-ALGORITHM

string Random_Selection(vector<string> &p) {

    int total_value = 0;
    vector<int> h(p.size());
    vector<int> rand_array;

    for (int i = 0; i < p.size(); ++i) {
        b_tool.set_state(p[i]);
        b_tool.fill_in_board();
        h[i] = b_tool.h_of_not_attack_pair();
        total_value += h[i];
    }

    for (int i = 0; i < p.size(); ++i) {
        for (int j = 0; j < h[i]; ++j) {
            rand_array.push_back(i);
        }
    }

    int rv = rand() % total_value;

    return p[rand_array[rv]];
}

string Reproduce(string x, string y) {
    int cut = rand() % 5;	// 0 1 2 3 4
    cut += 2;				// 2 3 4 5 6
    return x.substr(0, cut) + y.substr(cut);
}

bool Mutate(string &s, float rate) {
    int rand_mutate_pos = rand() % 64;
    string new_s = s;
    int h = 0;
    int new_h = 0;

    if (((float)(rand() % 1000) / 1000) < rate) {
        new_s[rand_mutate_pos / 8] = (rand_mutate_pos % 8) + '0';
        b_tool.set_state(new_s);
        b_tool.fill_in_board();
        new_h = b_tool.h_of_not_attack_pair();
        b_tool.set_state(s);
        b_tool.fill_in_board();
        h = b_tool.h_of_not_attack_pair();
        if (new_h >= h) s = new_s;						// 为加快收敛速度，只保留有利变异
        return true;
    }
    return false;
}

void print_p(const vector<string>& p) {
    for (auto str : p) {
        b_tool.set_state(str);
        b_tool.fill_in_board();
        cout << str << " : " << b_tool.h_of_not_attack_pair() << endl;
    }
    cout << endl;
}

bool Genetic_Algorithn(vector<string> &p, float mutate_rate) {
    vector<string> old_p = p;
    vector<string> new_p(p.size());

    for (int n = 0; n < 1000; ++n) {
        for (int i = 0; i < p.size(); ++i) {
            string x = Random_Selection(old_p);
            string y = Random_Selection(old_p);
            string child = Reproduce(x, y);
            Mutate(child, mutate_rate);
            new_p[i] = child;
            b_tool.set_state(child);
            b_tool.fill_in_board();
            if (b_tool.check(1)) {		// 若成功找到解，输出到 p[0] 上
                p[0] = child;
                generation += n;
                return true;
            }
        }

        old_p = new_p;
        // cout << endl << n + 1 << ":" << endl;
        // print_p(old_p);
    }


    p = old_p;							// 失败，但得到较好的种群
    return false;

}

bool GA_test1(int p_size = 4, float mutate_rate = 0.5) {

    vector<string> p(p_size);

    for (int i = 0; i < p_size; ++i) {
        b_tool.random_initial_state();
        b_tool.fill_in_board();
        p[i] = b_tool.get_state();
        cout << p[i] << " : " << b_tool.h_of_not_attack_pair() << endl;
    }

    if (Genetic_Algorithn(p, mutate_rate)) {
        b_tool.set_state(p[0]);
        b_tool.fill_in_board();
        b_tool.display(1);
        return true;
    }
    else {
        return false;
    }

}

void GA_test2(int p_size = 4, float mutate_rate = 0.5) {
    int count = 0;
    for (int i = 0; i < 1000; ++i) {
        cout << i << endl;
        if (GA_test1(p_size, mutate_rate)) ++count;
    }

    cout << "Genetic_Algorithm: " << endl
         << "Success Rate: " << float(count) / 1000 << " [" << count << "/1000]" << endl
         << "Success Average Generation: " << float(generation) / count << endl;

}

int main()
{
    srand(time(0));

    // 每次选择一个测试函数执行

//     SHC_test1();
     SHC_test2();

    // FCHC_test1();
    // FCHC_test2();

    // RRSHC_test1();
    // RRSHC_test2();

    // SA_test1();
    // SA_test2();

    // GA_test1();
    // GA_test2();

    return 0;
}

