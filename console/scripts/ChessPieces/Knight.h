#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(bool isWhite)
    : ChessPiece{isWhite, L'k'}
    {}
};