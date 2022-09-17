#include <iostream>
#include <string>

using namespace std;

/*int chess_match(int position_a, int position_0, int*** board) {
    if (position_0 == 7) return 0;
    else {
        if (board[position_a][position_0 + 1][2] != 1) {
            board[position_a][position_0 + 1][3] += board[position_a][position_0][3];
            chess_match(position_a, position_0 + 1, board);
        }
        if (position_a != 0) {
            if (board[position_a - 1][position_0 + 1][2] == 1) {
                board[position_a - 1][position_0 + 1][3] += board[position_a][position_0][3];
                chess_match(position_a - 1, position_0 + 1, board);
            }
        }
        if (position_a != 7) {
            if (board[position_a + 1][position_0 + 1][2] == 1) {
                board[position_a + 1][position_0 + 1][3] += board[position_a][position_0][3];
                chess_match(position_a + 1, position_0 + 1, board);
            }
        }
        return 0;
    }
}*/

int main() {
    const int size = 8;
    int*** board;

    board = new int** [size];
    for (int i = 0; i < size; i++) {
        board[i] = new int* [size];
        for (int j = 0; j < size; j++) board[i][j] = new int[4];
    }

    int correction_a = 97;
    int correction_0 = 49;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j][0] = i + correction_a;
            board[i][j][1] = j + correction_0;
            board[i][j][2] = 0;
            board[i][j][3] = 0;
            //cout.width(6);
            cout << char(board[i][j][0]) << char(board[i][j][1]) << ", " << board[i][j][2];
        }
        cout << '\n';
    }

    int n;
    cin >> n;
    string string;
    
    for (int i = 0; i < n; i++) {
        cin >> string;
        board[string[0] - correction_a][string[1] - correction_0][2] = 1;
    }


    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout.width(6);
            cout << char(board[i][j][0]) << char(board[i][j][1]) << ", " << board[i][j][2];
        }
        cout << '\n';
    }*/

    int* white_position = new int[2];
    cin >> string;
    white_position[0] = string[0] - correction_a;
    white_position[1] = string[1] - correction_0;
    //cout << white_position[0] << " " << white_position[1] << '\n';
    board[white_position[0]][white_position[1]][3] += 1;
    //chess_match(white_position[0], white_position[1], board);

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[j][i][2] != 1) board[j][i][3] += board[j][i - 1][3];
            if (board[j][i][2] == 1) {
                if (j != 0) board[j][i][3] += board[j - 1][i - 1][3];
                if (j != 7) board[j][i][3] += board[j + 1][i - 1][3];
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < size; i++) result += board[i][7][3];
    cout << result;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) delete[] board[i][j];
        delete[] board[i];
    }
    delete[] board;

	return 0;
}

