#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(bool isWhite)
    : ChessPiece{isWhite, L'B'}
    {}
};