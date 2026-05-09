#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "../Piece/Piece.h"

class Board
{
private:
    Piece board[8][8];
public:
    Board();
    ~Board();
    void showBoard(std::ostream& o);
};

#endif