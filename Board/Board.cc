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
        board[6][i] = Piece(PieceType::Pawn, PieceColor::White);

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

bool Board::isEmpty(Position square) const {
    return board[square.row][square.col].getType() == PieceType::None;
}

bool Board::isOpponentPiece(Piece p1, Piece p2) const {
    return p1.getColor() == p2.getColor();
}

bool Board::isRookLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Rook)
        throw std::invalid_argument("This piece is not a rook!");

    if (move.from.row != move.to.row && move.from.col != move.to.col)
        return false;

    int rowDir = 0, colDir = 0;
    if (move.from.row != move.to.row)
        rowDir = (move.to.row > move.from.row) ? 1 : -1;
    else
        colDir = (move.to.col > move.from.col) ? 1 : -1;

    int r = move.from.row + rowDir;
    int c = move.from.col + colDir;

    while (r != move.to.row || c != move.to.col) {
        if (!isEmpty({r, c}))
            return false;
        r += rowDir;
        c += colDir;
    }

    Piece dest = board[move.to.row][move.to.col];
    if (!isEmpty(move.to) && isOpponentPiece(dest, board[move.from.row][move.from.col]))
        return false;

    return true;
}