#include "ShortPieceFormatter.h"

std::string ShortPieceFormatter::Format(const BaseChessPiece& piece) const
{
    return piece.GetName() + " (" + static_cast<char>(piece.GetWcharChessPiece()) + ")";
}
