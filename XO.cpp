#include <iostream>
#include <random>
using namespace std;

class board {
private:
    int bl_size = 7;
    int moves = 1;
    int blank_spaces[9] = {};
    int mat[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool is_running = true;
    int winner;

    char mat_XO(int a) {
        if (a == 0) {
            return ' ';
        }
        else if (a == 1) {
            return 'O';
        }
        else if (a == 2) {
            return 'X';
        }
        return ' ';
    }

    void get_blank_spaces(int check_mat[9]) {
        int x = 0;
        for (int i = 0; i < 9; i++) {
            if (check_mat[i] == 0) {
                blank_spaces[x] = i;
                x += 1;
            }
        }

        bl_size = x;
    }

    int ran() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, bl_size - 1);

        int random_number = distr(gen);
        return random_number;
    }

    bool win_condition(int check_mat[9], int XO) {
        for (int i = 0; i < 3; i++) {
            if (check_mat[i] == XO && check_mat[i + 3] == XO && check_mat[i + 6] == XO) return true;
            if (check_mat[3 * i] == XO && check_mat[3 * i + 1] == XO && check_mat[3 * i + 2] == XO) return true;
        }
        if (check_mat[0] == XO && check_mat[4] == XO && check_mat[8] == XO) return true;
        if (check_mat[2] == XO && check_mat[4] == XO && check_mat[6] == XO) return true;

        return false;
    }

    int nextmove() {
        get_blank_spaces(mat);
        for (int x = 0; x < bl_size; x++)
        {
            cout << blank_spaces[x] << " ";
        }
        cout << endl;
        int copy_mat[9];
        for (int x = 0; x < 9; x++) {
            copy_mat[x] = mat[x];
        }

        get_blank_spaces(mat);

        for (int x = 0; x < bl_size; x++) {
            copy_mat[blank_spaces[x]] = 1;
            if (win_condition(copy_mat, 1)) {
                copy_mat[blank_spaces[x]] = 0;
                return blank_spaces[x];
            }
            copy_mat[blank_spaces[x]] = 0;
        }

        for (int y = 0; y < bl_size; y++) {
            copy_mat[blank_spaces[y]] = 2;
            if (win_condition(copy_mat, 2)) {
                copy_mat[blank_spaces[y]] = 0;
                return blank_spaces[y];
            }
            copy_mat[blank_spaces[y]] = 0;
        }

        for (int x = 0; x < bl_size; x++) {
            copy_mat[blank_spaces[x]] = 1;
            for (int y = 0; y < bl_size; y++) {
                if (y != x) {
                    copy_mat[blank_spaces[y]] = 1;
                    if (win_condition(copy_mat, 1)) {
                        copy_mat[blank_spaces[x]] = 0;
                        copy_mat[blank_spaces[y]] = 0;
                        return blank_spaces[y];
                    }
                    copy_mat[blank_spaces[y]] = 0;
                }
            }
            copy_mat[blank_spaces[x]] = 0;
        }

        return blank_spaces[ran()];
    }

public:
    void display() {
        get_blank_spaces(mat);
        cout << " " << mat_XO(mat[0]) << " | " << mat_XO(mat[1]) << " | " << mat_XO(mat[2]) << " " << endl;
        cout << "---+---+---" << endl;
        cout << " " << mat_XO(mat[3]) << " | " << mat_XO(mat[4]) << " | " << mat_XO(mat[5]) << " " << endl;
        cout << "---+---+---" << endl;
        cout << " " << mat_XO(mat[6]) << " | " << mat_XO(mat[7]) << " | " << mat_XO(mat[8]) << " " << endl;
    }

    void reference() {
        cout << "Choose the box" << endl;
        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl;
    }

    void game_loop() {
        while (is_running) {
            int in, index;
            cout << "\nBOX no : ";
            cin >> in;
            index = in - 1;

            if (mat[index] != 0) {
                cout << "Choose a correct box ;D\n";
                continue;
            }
            mat[index] = 2;
            if (win_condition(mat, 2)) {
                winner = 2;
                is_running = false;
                break;
            }

            if (moves == 9) {
                winner = 0;
                is_running = false;
                break;
            }

            int ai_move = nextmove();
            mat[ai_move] = 1;
            display();
            if (win_condition(mat, 1)) {
                winner = 1;
                is_running = false;
                break;
            }

            moves+=2;
            system("cls");
            display();
        }

        if (!is_running) {
            system("cls");
            display();
            if (winner == 0) {
                cout << "   DRAW,thappichita...\n";
            }
            else if (winner == 1) {
                cout << "   YOU LOST\nComputer kittalam thothu pora vekkama illa ;D\n";
            }
            else if (winner == 2) {
                cout << "YOU WON\nSeri palla kaattatha computer tha\n";
            }
        }
    }
    void reset() {
        bl_size = 9;
        moves = 1;
        for (int x = 0; x < 9; x++)
        {
            mat[x] = 0;
        }
        is_running = true;
    }
};

int main() {
    board b;
    cout << "MAMAE game aadriya :D\n\n";
    while (true) {
        system("cls");
        b.reference();
        b.game_loop();
        cout << "\n\nInnoru aaduriya ..?\n";
        cout << " yes na \"1\" aluthu\n illana \"0\" aluthu : ";
        bool next;
        cin >> next;
        if (!next) {
            system("cls");
            cout << "OOMBU";
            break;
        }
        else {
            system("cls");
            b.reset();
        }
    }
    return 0;
}
