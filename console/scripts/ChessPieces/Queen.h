#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(bool isWhite)
    : ChessPiece{isWhite, L'Q'}
    {}
};