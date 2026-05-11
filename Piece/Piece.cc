#include "Piece.h"

Piece::Piece() : type(PieceType::None), color(PieceColor::None) {}

Piece::Piece(PieceType t, PieceColor c) : type(t), color(c) {}

Piece::~Piece() {}

PieceType Piece::getType() const {
    return type;
}
PieceColor Piece::getColor() const {
    return color;
}

void Piece::showPiece(std::ostream& o) const {
    switch (type)
    {
    case PieceType::Pawn:
        o << 'P';
        break;
    case PieceType::Rook:
        o << 'R';
        break;
    case PieceType::Knight:
        o << 'K';
        break;
    case PieceType::Bishop:
        o << 'B';
        break;
    case PieceType::King:
        o << 'K';
        break;
    case PieceType::Queen:
        o << 'Q';
        break;
    
    default:
        o << ' ';
    }
}

std::ostream& operator<<(std::ostream& os, const Piece& P) {
    P.showPiece(os);
    return os;
}

std::string pieceTypeToName(PieceType type) {
    switch (type) {
        case PieceType::Pawn:   return "pawn";
        case PieceType::Rook:   return "rook";
        case PieceType::Knight: return "knight";
        case PieceType::Bishop: return "bishop";
        case PieceType::Queen:  return "queen";
        case PieceType::King:   return "king";
        default:                return "none";
    }
}

std::string pieceColorToName(PieceColor color) {
    switch (color) {
        case PieceColor::White: return "w";
        case PieceColor::Black: return "b";
        default:                return "none";
    }
}
