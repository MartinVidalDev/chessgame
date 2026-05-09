#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "../Piece/Piece.h"
#include "../Types/Types.h"

class Board
{
private:
    Piece board[8][8];
public:
    Board();
    ~Board();

    void showBoard(std::ostream& o);

    bool isEmpty(Position square) const;
    bool isOpponentPiece(Piece p1, Piece p2) const;
    bool isRookLegalMove(Move move) const;
};

#endif