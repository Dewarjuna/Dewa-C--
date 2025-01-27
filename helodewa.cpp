#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define chessnya
enum Piece {
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

// warna chess
enum Color {
    NONE,
    WHITE,
    BLACK
};

// Papan
struct Square {
    Piece piece;
    Color color;
};

Square board[8][8];

// Init papannya
void initializeBoard() {
    // Init yg kosong di papan
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].piece = EMPTY;
            board[i][j].color = NONE;
        }
    }

    // Init si putih
    board[0][0] = {ROOK, WHITE};
    board[0][1] = {KNIGHT, WHITE};
    board[0][2] = {BISHOP, WHITE};
    board[0][3] = {QUEEN, WHITE};
    board[0][4] = {KING, WHITE};
    board[0][5] = {BISHOP, WHITE};
    board[0][6] = {KNIGHT, WHITE};
    board[0][7] = {ROOK, WHITE};
    for (int i = 0; i < 8; i++) {
        board[1][i] = {PAWN, WHITE};
    }

    // Init si HITAM LEGAM
    board[7][0] = {ROOK, BLACK};
    board[7][1] = {KNIGHT, BLACK};
    board[7][2] = {BISHOP, BLACK};
    board[7][3] = {QUEEN, BLACK};
    board[7][4] = {KING, BLACK};
    board[7][5] = {BISHOP, BLACK};
    board[7][6] = {KNIGHT, BLACK};
    board[7][7] = {ROOK, BLACK};
    for (int i = 0; i < 8; i++) {
        board[6][i] = {PAWN, BLACK};
    }
}

// Tampilin papannya
void displayBoard() {
    cout << "  a b c d e f g h" << endl;
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            switch (board[i][j].piece) {
                case EMPTY: cout << "."; break;
                case PAWN: cout << (board[i][j].color == WHITE ? "P" : "p"); break;
                case ROOK: cout << (board[i][j].color == WHITE ? "R" : "r"); break;
                case KNIGHT: cout << (board[i][j].color == WHITE ? "N" : "n"); break;
                case BISHOP: cout << (board[i][j].color == WHITE ? "B" : "b"); break;
                case QUEEN: cout << (board[i][j].color == WHITE ? "Q" : "q"); break;
                case KING: cout << (board[i][j].color == WHITE ? "K" : "k"); break;
            }
            cout << " ";
        }
        cout << 8 - i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

// Ngubah notasi aljabar jadi indeks papannya
bool parseMove(string move, int &x1, int &y1, int &x2, int &y2) {
    if (move.length() != 5 || move[2] != ' ') return false;
    y1 = move[0] - 'a';
    x1 = '8' - move[1];
    y2 = move[3] - 'a';
    x2 = '8' - move[4];
    return x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && x2 >= 0 && x2 < 8 && y2 >= 0 && y2 < 8;
}

// ngecek kalo movenya valid
bool isValidMove(int x1, int y1, int x2, int y2, Color turn) {
    if (board[x1][y1].color != turn) return false;
    if (board[x2][y2].color == turn) return false;
    // placeholder buat nambah rules
    return true;
}

// mulai giliran playernya
void makeMove(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1].piece = EMPTY;
    board[x1][y1].color = NONE;
}

int main() {
    initializeBoard();
    Color turn = WHITE;
    string move;
    int x1, y1, x2, y2;

    while (true) {
        displayBoard();
        cout << (turn == WHITE ? "White" : "Black") << "'s move: ";
        getline(cin, move);

        if (!parseMove(move, x1, y1, x2, y2)) {
            cout << "Invalid move format. Use format like 'e2 e4'." << endl;
            continue;
        }

        if (!isValidMove(x1, y1, x2, y2, turn)) {
            cout << "Invalid move." << endl;
            continue;
        }

        makeMove(x1, y1, x2, y2);
        turn = (turn == WHITE ? BLACK : WHITE);
    }

    return 0;
}