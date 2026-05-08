#include <iostream>
#include "Board/Board.h"

int main() {
    Board board;
    std::cout << "Chess game" << "\n";

    board.showBoard(std::cout);

    return 0;
}