#include <iostream>
#include <vector>
using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

void printBoard(const vector<vector<char> >& board) {
    cout << "\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "-----------------------------\n";
    cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
    cout << "-----------------------------\n";
}

bool isValidMove(const vector<vector<char> >& board, int col) {
    return col >= 0 && col < COLS && board[0][col] == EMPTY;
}

void makeMove(vector<vector<char> >& board, int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            break;
        }
    }
}

bool isBoardFull(const vector<vector<char> >& board) {
    for (int j = 0; j < COLS; ++j) {
        if (board[0][j] == EMPTY) {
            return false;
        }
    }
    return true;
}

bool checkWin(const vector<vector<char> >& board, char player) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player &&
                board[i][j + 2] == player && board[i][j + 3] == player)
                return true;
        }
    }

    for (int i = 0; i <= ROWS - 4; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == player && board[i + 1][j] == player &&
                board[i + 2][j] == player && board[i + 3][j] == player)
                return true;
        }
    }

    for (int i = 0; i <= ROWS - 4; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player && board[i + 3][j + 3] == player)
                return true;
        }
    }

    for (int i = 3; i < ROWS; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i - 1][j + 1] == player &&
                board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
                return true;
        }
    }

    return false;
}

int main() {
    vector<vector<char> > board(ROWS, vector<char>(COLS, EMPTY));
    bool player1Turn = true;

    cout << "Welcome to Connect Four!\n";

    while (true) {
        printBoard(board);
        char currentPlayer = player1Turn ? PLAYER1 : PLAYER2;
        cout << "Player " << currentPlayer << ", choose column (1-7): ";

        int col;
        cin >> col;
        col--;

        if (!cin || col < 0 || col >= COLS) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (isValidMove(board, col)) {
            makeMove(board, col, currentPlayer);

            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }

            if (isBoardFull(board)) {
                printBoard(board);
                cout << "It's a draw!\n";
                break;
            }

            player1Turn = !player1Turn;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    return 0;
}

