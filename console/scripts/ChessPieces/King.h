#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(bool isWhite)
    : ChessPiece{isWhite, L'K'}
    {}
};