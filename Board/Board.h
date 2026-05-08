#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>

class Board
{
private:
    int board[8][8];
public:
    Board();
    ~Board();
    void showBoard(std::ostream& o);
};

#endif