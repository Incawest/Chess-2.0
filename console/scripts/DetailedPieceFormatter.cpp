#include "DetailedPieceFormatter.h"

std::string DetailedPieceFormatter::Format(const BaseChessPiece& piece) const
{
    return piece.GetName() + ": symbol = " + static_cast<char>(piece.GetWcharChessPiece())
        + ", value = " + std::to_string(piece.GetChessPieceValue())
        + ", is white = " + std::to_string(piece.GetIsWhitePiece())
        + ", index = " + std::to_string(piece.GetIndexInChessboard());
}
