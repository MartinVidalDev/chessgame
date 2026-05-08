#include "Board.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
}

Board::~Board() {}

void Board::showBoard(std::ostream& o) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            o << '|' << board[i][j] << '|';
        }
        o << '\n';
    }
}