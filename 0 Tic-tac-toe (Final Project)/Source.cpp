#include <iomanip>
#include <iostream>

using namespace std;

class Tic_tac_toe {
public:
    int board[3][3];
    int turn;
    int xi, oi;
    int value;
    int xw, ow;

    static const int INF_MAX = 999;
    static const int INF_MIN = -999;
    static const int X = 1;
    static const int O = -1;
    static const int COMPUTER = -1;
    static const int HUMAN = 1;

    Tic_tac_toe() {
        memset(board, 0, sizeof(board));
        turn = COMPUTER;
    }

    bool x_full() {
        return
            (board[0][0] + board[0][1] + board[0][2] == 3) ||
            (board[1][0] + board[1][1] + board[1][2] == 3) ||
            (board[2][0] + board[2][1] + board[2][2] == 3) ||
            (board[0][0] + board[1][0] + board[2][0] == 3) ||
            (board[0][1] + board[1][1] + board[2][1] == 3) ||
            (board[0][2] + board[1][2] + board[2][2] == 3) ||
            (board[0][0] + board[1][1] + board[2][2] == 3) ||
            (board[0][2] + board[1][1] + board[2][0] == 3);
    }

    bool o_full() {
        return
            (board[0][0] + board[0][1] + board[0][2] == -3) ||
            (board[1][0] + board[1][1] + board[1][2] == -3) ||
            (board[2][0] + board[2][1] + board[2][2] == -3) ||
            (board[0][0] + board[1][0] + board[2][0] == -3) ||
            (board[0][1] + board[1][1] + board[2][1] == -3) ||
            (board[0][2] + board[1][2] + board[2][2] == -3) ||
            (board[0][0] + board[1][1] + board[2][2] == -3) ||
            (board[0][2] + board[1][1] + board[2][0] == -3);
    }

    void compute_state() {

        xi = 0;
        oi = 0;

        if ((board[0][0] != O) && (board[0][1] == 0 != O) && (board[0][2] == 0 != O)) { xi++; }
        if ((board[1][0] != O) && (board[1][1] == 0 != O) && (board[1][2] == 0 != O)) { xi++; }
        if ((board[2][0] != O) && (board[2][1] == 0 != O) && (board[2][2] == 0 != O)) { xi++; }
        if ((board[0][0] != O) && (board[1][0] == 0 != O) && (board[2][0] == 0 != O)) { xi++; }
        if ((board[0][1] != O) && (board[1][1] == 0 != O) && (board[2][1] == 0 != O)) { xi++; }
        if ((board[0][2] != O) && (board[1][2] == 0 != O) && (board[2][2] == 0 != O)) { xi++; }
        if ((board[0][0] != O) && (board[1][1] == 0 != O) && (board[2][2] == 0 != O)) { xi++; }
        if ((board[0][2] != O) && (board[1][1] == 0 != O) && (board[2][0] == 0 != O)) { xi++; }

        if ((board[0][0] != X) && (board[0][1] != X) && (board[0][2] != X)) { oi++; }
        if ((board[1][0] != X) && (board[1][1] != X) && (board[1][2] != X)) { oi++; }
        if ((board[2][0] != X) && (board[2][1] != X) && (board[2][2] != X)) { oi++; }
        if ((board[0][0] != X) && (board[1][0] != X) && (board[2][0] != X)) { oi++; }
        if ((board[0][1] != X) && (board[1][1] != X) && (board[2][1] != X)) { oi++; }
        if ((board[0][2] != X) && (board[1][2] != X) && (board[2][2] != X)) { oi++; }
        if ((board[0][0] != X) && (board[1][1] != X) && (board[2][2] != X)) { oi++; }
        if ((board[0][2] != X) && (board[1][1] != X) && (board[2][0] != X)) { oi++; }

        value = xi - oi;

        if (x_full()) { value = INF_MAX; }

        if (o_full()) { value = INF_MIN; }

    }

    int waitfor() {
        int x, y;
        cin >> x >> y;
        if (x < 1 || x > 3 || y < 1 || y > 3) {
            printf("�۾���������С��������߶��¡�\n");
            waitfor();
        }
        else if (board[x - 1][y - 1] == X || board[x - 1][y - 1] == O) {
            printf("������Ӷ��ˣ�������ɡ�\n");
            waitfor();
        }
        else { board[x - 1][y - 1] = turn; }
        return 0;
    }

    int reverse(int turn_now) {
        if (turn_now = COMPUTER) {
            return HUMAN;
        }
        else {
            return COMPUTER;
        }
    }

    int max1() {
        int max = INF_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {//��λ�ÿ���
                    board[i][j] = turn;
                    compute_state();
                    if (value == INF_MIN) {
                        board[i][j] = 0;
                        return INF_MIN;
                    }
                    if (value > max) { max = value; }
                    board[i][j] = 0;
                }
            }
        }
        return max;
    }

    int min1() {
        int min = INF_MAX;
        int best;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {//��λ�ÿ���
                    board[i][j] = reverse(turn);
                    compute_state();
                    value = max1();
                    if (min >= value) {
                        min = value;
                        best = i * 10 + j;
                    }
                    board[i][j] = 0;
                }
            }
        }
        board[best / 10][best % 10] = -turn;
        return 0;
    }

    int min2() {
        int min = INF_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {//��λ�ÿ���
                    board[i][j] = turn;
                    compute_state();
                    if (value == INF_MAX) {
                        board[i][j] = 0;
                        return INF_MAX;
                    }
                    if (value < min)
                        min = value;
                    board[i][j] = 0;
                }
            }
        }
        return min;
    }

    int max2() {
        int max = INF_MIN;
        int best;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {//��λ�ÿ���
                    board[i][j] = reverse(turn);
                    compute_state();
                    value = min2();
                    if (max <= value) {
                        max = value;
                        best = i * 10 + j;
                    }
                    board[i][j] = 0;
                }
            }
        }
        board[best / 10][best % 10] = reverse(turn);
        return 0;
    }

    void printstate() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == X)
                    cout << "x  ";
                else if (board[i][j] == O)
                    cout << "o  ";
                else
                    cout << "*  ";
            }
            cout << endl;
        }
    }

    int init() {
        printf("initial state\n");
        compute_state();
        printstate();
        if (turn == HUMAN) {
            while (xi != 0 && oi != 0) {
                printf("\nyour turn\n");
                waitfor();
                compute_state();
                printstate();
                if (value == INF_MAX) {
                    printf("EXECELLENT!\nYOU WIN\n");
                    return 0;
                }
                if (xi == 0 && oi == 0) {
                    printf("DRAW\n");
                    return 0;
                }
                printf("\ncomputer turn\n");
                min1();
                compute_state();
                printstate();
                if (value == INF_MIN) {
                    printf("YOU LOSE\n");
                    return 0;
                }
                if (xi == 0 && oi == 0) {
                    printf("DRAW\n");
                    return 0;
                }
            }
        }
        else if (turn == COMPUTER) {
            while (xi != 0 && oi != 0) {
                printf("\ncomputer turn\n");
                max2();
                compute_state();
                printstate();
                if (value == INF_MAX) {
                    printf("YOU LOSE\n");
                    return 0;
                }
                if (xi == 0 && oi == 0) {
                    printf("DRAW\n");
                    return 0;
                }
                printf("\nyour turn\n");
                waitfor();
                compute_state();
                printstate();
                if (value == INF_MIN) {
                    printf("EXECELLENT!\nYOU WIN\n");
                    return 0;
                }
                if (xi == 0 && oi == 0) {
                    printf("DRAW\n");
                    return 0;
                }
            }
        }
        return 0;
    }

};

int main()
{
    Tic_tac_toe game;
    game.init();
    return 0;
}