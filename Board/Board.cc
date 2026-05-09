#include "Board.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Piece();
        }
    }

    board[0][0] = Piece(PieceType::Rook, PieceColor::Black);
    board[0][1] = Piece(PieceType::Knight, PieceColor::Black);
    board[0][2] = Piece(PieceType::Bishop, PieceColor::Black);
    board[0][3] = Piece(PieceType::Queen, PieceColor::Black);
    board[0][4] = Piece(PieceType::King, PieceColor::Black);
    board[0][5] = Piece(PieceType::Bishop, PieceColor::Black);
    board[0][6] = Piece(PieceType::Knight, PieceColor::Black);
    board[0][7] = Piece(PieceType::Rook, PieceColor::Black);

    for (int i = 0; i < 8; i++)
        board[1][i] = Piece(PieceType::Pawn, PieceColor::Black);

    for (int i = 0; i < 8; i++)
        board[6][i] = Piece(PieceType::Pawn, PieceColor::Black);

    board[7][0] = Piece(PieceType::Rook, PieceColor::White);
    board[7][1] = Piece(PieceType::Knight, PieceColor::White);
    board[7][2] = Piece(PieceType::Bishop, PieceColor::White);
    board[7][3] = Piece(PieceType::Queen, PieceColor::White);
    board[7][4] = Piece(PieceType::King, PieceColor::White);
    board[7][5] = Piece(PieceType::Bishop, PieceColor::White);
    board[7][6] = Piece(PieceType::Knight, PieceColor::White);
    board[7][7] = Piece(PieceType::Rook, PieceColor::White);
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