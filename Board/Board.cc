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
    return p1.getColor() != p2.getColor();
}

bool Board::isValidPositionInBoard(Position p) const {
    return (p.row >= 0 && p.row <= 7) && (p.col >= 0 && p.col <= 7);
}

bool Board::isRookLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Rook)
        throw std::invalid_argument("This piece is not a rook!");

    if (!isValidPositionInBoard(move.to)) {
        return false;
    }

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
    if (!isEmpty(move.to) && !isOpponentPiece(dest, board[move.from.row][move.from.col]))
        return false;

    return true;
}

bool Board::isKnightLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Knight)
        throw std::invalid_argument("This piece is not a knight!");

    if (!isValidPositionInBoard(move.to)) {
        return false;
    }

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if ((rowDiff != 2 || colDiff != 1) && (rowDiff != 1 || colDiff != 2)) {
        return false;
    }

    if (isEmpty(move.to)) {
        return true;
    }

    if (isOpponentPiece(board[move.to.row][move.to.col], board[move.from.row][move.from.col])) {
        return true;
    }

    return false;
}

bool Board::isBishopLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Bishop)
        throw std::invalid_argument("This piece is not a bishop!");
    
    if (!isValidPositionInBoard(move.to))
        return false;

    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;

    if (abs(rowDiff) != abs(colDiff))
        return false;

    int rowStep = (rowDiff > 0) ? 1 : -1;
    int colStep = (colDiff > 0) ? 1 : -1;

    int r = move.from.row + rowStep;
    int c = move.from.col + colStep;

    while (r != move.to.row) {
        if (!isEmpty({r, c}))
            return false;
        r = r + rowStep;
        c = c + colStep;
    }

    if (isEmpty(move.to))
        return true;

    if (isOpponentPiece(board[move.to.row][move.to.col], board[move.from.row][move.from.col]))
        return true;

    return false;
}