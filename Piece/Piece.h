#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>

enum class PieceColor {
    White,
    Black,
    None
};

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    King,
    Queen,
    None
};

class Piece
{
private:
    PieceType type;
    PieceColor color;
public:
    Piece();
    Piece(PieceType t, PieceColor c);
    ~Piece();
    
    PieceType getType() const;
    PieceColor getColor() const;

    void showPiece(std::ostream& o) const;
};

std::ostream& operator<<(std::ostream& os, const Piece& P);
std::string pieceTypeToName(PieceType type);
std::string pieceColorToName(PieceColor color);

#endif