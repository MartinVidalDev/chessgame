#include <iostream>
#include "Board/Board.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using TextureKey = std::pair<PieceType, PieceColor>;

static bool loadAllPieceTextures(std::map<TextureKey, sf::Texture>& textureMap) {
    const PieceType pieceTypes[] = {
        PieceType::Pawn, PieceType::Rook, PieceType::Knight,
        PieceType::Bishop, PieceType::Queen, PieceType::King
    };
    const PieceColor colors[] = { PieceColor::White, PieceColor::Black };

    for (PieceColor color : colors) {
        for (PieceType type : pieceTypes) {
            std::string path = "../Assets/Pieces/" + pieceColorToName(color) + "_" + pieceTypeToName(type) + ".png";
            sf::Texture tex;
            if (!tex.loadFromFile(path)) {
                std::cerr << "Failed to load texture: " << path << '\n';
                return false;
            }
            textureMap[{type, color}] = std::move(tex);
        }
    }
    return true;
}

int main() {
    Board board;

    std::map<TextureKey, sf::Texture> textureMap;
    if (!loadAllPieceTextures(textureMap)) {
        return 1;
    }

    const float tile = 80.f;
    const float margin = 20.f;

    sf::RenderWindow window(
        sf::VideoMode(
            static_cast<unsigned int>(8 * tile + 2 * margin),
            static_cast<unsigned int>(8 * tile + 2 * margin)
        ),
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

                Piece piece = board.getPieceAt(row, col);
                if (piece.getType() != PieceType::None) {
                    TextureKey key = {piece.getType(), piece.getColor()};
                    sf::Sprite sprite(textureMap.at(key));

                    float scaleX = tile / sprite.getLocalBounds().width;
                    float scaleY = tile / sprite.getLocalBounds().height;
                    sprite.setScale(scaleX, scaleY);

                    sprite.setPosition(margin + col * tile, margin + row * tile);
                    window.draw(sprite);
                }                
            }
        }

        window.display();
    }

    return 0;
}