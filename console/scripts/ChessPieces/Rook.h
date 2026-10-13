#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(bool isWhite)
    : ChessPiece(isWhite, L'R')
    {}
};