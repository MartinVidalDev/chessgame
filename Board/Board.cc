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

Piece Board::getPieceAt(int row, int col) const {
    return board[row][col];
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
    if (!isEmpty(move.to) && !isOpponentPiece(dest, board[move.from.row][move.from.col]))
        return false;

    return true;
}

bool Board::isKnightLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Knight)
        throw std::invalid_argument("This piece is not a knight!");

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

bool Board::isQueenLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Queen)
        throw std::invalid_argument("This piece is not a queen!");

    if (move.from.row == move.to.row && move.from.col == move.to.col)
        return false;

    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;

    bool isStraight = (rowDiff == 0) || (colDiff == 0);
    bool isDiagonal = abs(rowDiff) == abs(colDiff);

    if (!isStraight && !isDiagonal)
        return false;
    
    int rowStep = 0;
    int colStep = 0;

    if (rowDiff != 0)
        rowStep = (rowDiff > 0) ? 1 : -1;
    if (colDiff != 0)
        colStep = (colDiff > 0) ? 1 : -1;

    int r = move.from.row + rowStep;
    int c = move.from.col + colStep;

    while (r != move.to.row || c != move.to.col) {
        if (!isEmpty({r, c}))
            return false;
        r += rowStep;
        c += colStep;
    }

    if (isEmpty(move.to))
        return true;

    if (isOpponentPiece(board[move.to.row][move.to.col], board[move.from.row][move.from.col]))
        return true;

    return false;
}

bool Board::isKingLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::King)
        throw std::invalid_argument("This piece is not a king!");

    if (move.from.row == move.to.row && move.from.col == move.to.col)
        return false;

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (rowDiff > 1 || colDiff > 1)
        return false;

    if (isEmpty(move.to))
        return true;

    if (isOpponentPiece(board[move.to.row][move.to.col], board[move.from.row][move.from.col]))
        return true;

    return false;
}

bool Board::isPawnLegalMove(Move move) const {
    if (board[move.from.row][move.from.col].getType() != PieceType::Pawn)
        throw std::invalid_argument("This piece is not a pawn!");

    if (move.from.row == move.to.row && move.from.col == move.to.col)
        return false;

    PieceColor pawnColor = board[move.from.row][move.from.col].getColor();
    int forwardDir = 1;

    if (pawnColor == PieceColor::White)
        forwardDir = -1;

    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;

    if (rowDiff == forwardDir && colDiff == 0)
        return isEmpty(move.to);

    if (rowDiff == forwardDir * 2 && colDiff == 0) {
        int startRow = (pawnColor == PieceColor::White) ? 6 : 1;
        if (move.from.row != startRow)
            return false;

        int intermediateRow = move.from.row + forwardDir;
        if (!isEmpty({intermediateRow, move.from.col}))
            return false;

        return isEmpty(move.to);
    }

    if (rowDiff == forwardDir && abs(colDiff) == 1) {
        if (isEmpty(move.to))
            return false;
        return isOpponentPiece(board[move.to.row][move.to.col], board[move.from.row][move.from.col]);
    }

    return false;
}

bool Board::isPseudoLegalMove(Move move) const {
    if (!isValidPositionInBoard(move.from) || !isValidPositionInBoard(move.to))
        return false;

    if (isEmpty(move.from))
        return false;

    switch (board[move.from.row][move.from.col].getType())
    {
        case PieceType::Rook:
            return isRookLegalMove(move);
        case PieceType::Knight:
            return isKnightLegalMove(move);
        case PieceType::Bishop:
            return isBishopLegalMove(move);
        case PieceType::Queen:
            return isQueenLegalMove(move);
        case PieceType::King:
            return isKingLegalMove(move);
        case PieceType::Pawn:
            return isPawnLegalMove(move);
        default:
            return false;
    }
}

bool Board::isSquareUnderAttack(Position square, PieceColor byColor) const {
    if (!isValidPositionInBoard(square))
        return false;

    int knightOffsets[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for (const auto& offset : knightOffsets) {
        int r = square.row + offset[0];
        int c = square.col + offset[1];
        Position p{r, c};
        if (!isValidPositionInBoard(p))
            continue;

        Piece piece = board[r][c];
        if (piece.getColor() == byColor && piece.getType() == PieceType::Knight)
            return true;
    }

    int kingOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    for (const auto& offset : kingOffsets) {
        int r = square.row + offset[0];
        int c = square.col + offset[1];
        Position p{r, c};
        if (!isValidPositionInBoard(p))
            continue;

        Piece piece = board[r][c];
        if (piece.getColor() == byColor && piece.getType() == PieceType::King)
            return true;
    }

    int pawnRow = square.row + ((byColor == PieceColor::White) ? 1 : -1);
    int pawnCols[2] = {square.col - 1, square.col + 1};
    for (int pawnCol : pawnCols) {
        Position p{pawnRow, pawnCol};
        if (!isValidPositionInBoard(p))
            continue;

        Piece piece = board[pawnRow][pawnCol];
        if (piece.getColor() == byColor && piece.getType() == PieceType::Pawn)
            return true;
    }

    int rookDirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& dir : rookDirs) {
        int r = square.row + dir[0];
        int c = square.col + dir[1];
        while (isValidPositionInBoard({r, c})) {
            Piece piece = board[r][c];
            if (piece.getType() != PieceType::None) {
                if (piece.getColor() == byColor &&
                    (piece.getType() == PieceType::Rook || piece.getType() == PieceType::Queen)) {
                    return true;
                }
                break;
            }
            r += dir[0];
            c += dir[1];
        }
    }

    int bishopDirs[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (const auto& dir : bishopDirs) {
        int r = square.row + dir[0];
        int c = square.col + dir[1];
        while (isValidPositionInBoard({r, c})) {
            Piece piece = board[r][c];
            if (piece.getType() != PieceType::None) {
                if (piece.getColor() == byColor &&
                    (piece.getType() == PieceType::Bishop || piece.getType() == PieceType::Queen)) {
                    return true;
                }
                break;
            }
            r += dir[0];
            c += dir[1];
        }
    }

    return false;
}

bool Board::isCastlingMove(Move move) const {
    if (!isValidPositionInBoard(move.from) || !isValidPositionInBoard(move.to))
        return false;

    Piece piece = board[move.from.row][move.from.col];
    return piece.getType() == PieceType::King &&
           move.from.row == move.to.row &&
           abs(move.to.col - move.from.col) == 2;
}

bool Board::isLegalMove(Move move) const {
    if (!isValidPositionInBoard(move.from) || !isValidPositionInBoard(move.to))
        return false;

    if (move.from.row == move.to.row && move.from.col == move.to.col)
        return false;

    if (isEmpty(move.from))
        return false;

    Piece mover = board[move.from.row][move.from.col];
    PieceColor moverColor = mover.getColor();

    if (isCastlingMove(move)) {
        PieceColor opponent = (moverColor == PieceColor::White) ? PieceColor::Black : PieceColor::White;
        int homeRow = (moverColor == PieceColor::White) ? 7 : 0;

        if (move.from.row != homeRow || move.from.col != 4)
            return false;

        bool kingSide = (move.to.col == 6);
        bool queenSide = (move.to.col == 2);
        if (!kingSide && !queenSide)
            return false;

        if (mover.hasMoved())
            return false;

        int rookCol = kingSide ? 7 : 0;
        Piece rook = board[homeRow][rookCol];
        if (rook.getType() != PieceType::Rook || rook.getColor() != moverColor)
            return false;

        if (rook.hasMoved())
            return false;

        if (kingSide) {
            if (!isEmpty({homeRow, 5}) || !isEmpty({homeRow, 6}))
                return false;
        } else {
            if (!isEmpty({homeRow, 1}) || !isEmpty({homeRow, 2}) || !isEmpty({homeRow, 3}))
                return false;
        }

        int throughCol = kingSide ? 5 : 3;
        if (isSquareUnderAttack({homeRow, 4}, opponent) ||
            isSquareUnderAttack({homeRow, throughCol}, opponent) ||
            isSquareUnderAttack({homeRow, move.to.col}, opponent)) {
            return false;
        }

        return true;
    }

    if (!isPseudoLegalMove(move))
        return false;

    Board simulated = *this;
    simulated.board[move.to.row][move.to.col] = simulated.board[move.from.row][move.from.col];
    simulated.board[move.from.row][move.from.col] = Piece();

    if (simulated.isInCheck(moverColor))
        return false;

    return true;
}

void Board::makeMove(Move move) {
    if (!isLegalMove(move))
        return;

    Piece moving = board[move.from.row][move.from.col];
    moving.setMoved(true);

    if (isCastlingMove(move)) {
        int row = move.from.row;
        bool kingSide = (move.to.col == 6);

        int rookFromCol = kingSide ? 7 : 0;
        int rookToCol = kingSide ? 5 : 3;

        Piece rook = board[row][rookFromCol];
        rook.setMoved(true);

        board[move.to.row][move.to.col] = moving;
        board[move.from.row][move.from.col] = Piece();

        board[row][rookToCol] = rook;
        board[row][rookFromCol] = Piece();
        return;
    }

    board[move.to.row][move.to.col] = moving;
    board[move.from.row][move.from.col] = Piece();
}

bool Board::canPromoteAt(Position square) const {
    if (!isValidPositionInBoard(square))
        return false;

    Piece piece = board[square.row][square.col];
    if (piece.getType() != PieceType::Pawn)
        return false;

    return (piece.getColor() == PieceColor::White && square.row == 0) ||
           (piece.getColor() == PieceColor::Black && square.row == 7);
}

bool Board::promotePawn(Position square, PieceType newType) {
    if (!canPromoteAt(square))
        return false;

    if (newType != PieceType::Queen && newType != PieceType::Rook &&
        newType != PieceType::Bishop && newType != PieceType::Knight) {
        return false;
    }

    PieceColor color = board[square.row][square.col].getColor();
    board[square.row][square.col] = Piece(newType, color, true);
    return true;
}

bool Board::isInCheck(PieceColor color) const {
    Position kingPos{-1, -1};

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = board[row][col];
            if (piece.getType() == PieceType::King && piece.getColor() == color) {
                kingPos = Position{row, col};
            }
        }
    }

    if (!isValidPositionInBoard(kingPos))
        return false;

    PieceColor opponent = (color == PieceColor::White) ? PieceColor::Black : PieceColor::White;
    return isSquareUnderAttack(kingPos, opponent);
}

bool Board::hasAnyLegalMove(PieceColor color) const {
    for (int fromRow = 0; fromRow < 8; ++fromRow) {
        for (int fromCol = 0; fromCol < 8; ++fromCol) {
            Piece piece = board[fromRow][fromCol];
            if (piece.getColor() != color)
                continue;

            for (int toRow = 0; toRow < 8; ++toRow) {
                for (int toCol = 0; toCol < 8; ++toCol) {
                    Move move{{fromRow, fromCol}, {toRow, toCol}};
                    if (isLegalMove(move))
                        return true;
                }
            }
        }
    }

    return false;
}
