#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "../Piece/Piece.h"
#include "../Types/Types.h"

class Board
{
private:
    Piece board[8][8];

    bool isPseudoLegalMove(Move move) const;
    bool isSquareUnderAttack(Position square, PieceColor byColor) const;
    bool isCastlingMove(Move move) const;
public:
    Board();
    ~Board();

    void showBoard(std::ostream& o);

    bool isEmpty(Position square) const;
    bool isOpponentPiece(Piece p1, Piece p2) const;
    bool isValidPositionInBoard(Position p) const;
    Piece getPieceAt(int row, int col) const;

    bool isRookLegalMove(Move move) const;
    bool isKnightLegalMove(Move move) const;
    bool isBishopLegalMove(Move move) const;
    bool isQueenLegalMove(Move move) const;
    bool isKingLegalMove(Move move) const;
    bool isPawnLegalMove(Move move) const;

    bool isLegalMove(Move move) const;
    void makeMove(Move move);
    bool canPromoteAt(Position square) const;
    bool promotePawn(Position square, PieceType newType);
    bool isInCheck(PieceColor color) const;
    bool hasAnyLegalMove(PieceColor color) const;
    bool isCheckmate(PieceColor color) const;
    bool isStalemate(PieceColor color) const;
};

#endif