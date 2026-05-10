#include <iostream>
#include "Board/Board.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    // Board board;
    // std::cout << "Chess game" << "\n";

    // board.showBoard(std::cout);

    // Move m1{{0, 0}, {0, 0}};
    // Position pos{7,8};
    // Move m2{{0, 1}, {0, 1}};
    // Move m3{{0, 2}, {0, 2}};
    // Move m4{{0, 3}, {7, 3}};
    // Move m5{{0, 4}, {1, 4}};
    // Move m6{{6, 0}, {5, 1}};

    // std::cout << "Valid Position:" << board.isValidPositionInBoard(pos) << '\n';

    // std::cout << "Rook legal move:" << board.isRookLegalMove(m1) << '\n';

    // std::cout << "Knight legal move:" << board.isKnightLegalMove(m2) << '\n';

    // std::cout << "Bishop legal move:" << board.isBishopLegalMove(m3) << '\n';

    // std::cout << "Queen legal move:" << board.isQueenLegalMove(m4) << '\n';

    // std::cout << "King legal move:" << board.isKingLegalMove(m5) << '\n';

    // std::cout << "Pawn legal move:" << board.isPawnLegalMove(m6) << '\n';

    Board board;

    const float tile = 80.f;
    const float margin = 20.f;

    sf::RenderWindow window(
        sf::VideoMode(static_cast<unsigned int>(8 * tile + 2 * margin),
                    static_cast<unsigned int>(8 * tile + 2 * margin)),
        "Chess"
    );

    sf::Color light = sf::Color::White;
    sf::Color dark  = sf::Color(80, 140, 80);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                sf::RectangleShape square(sf::Vector2f(tile, tile));
                square.setPosition(margin + col * tile, margin + row * tile);

                bool isLight = ((row + col) % 2 == 0);
                square.setFillColor(isLight ? light : dark);

                window.draw(square);
            }
        }

        window.display();
    }
    return 0;
}