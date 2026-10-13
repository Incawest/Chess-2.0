#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(bool isWhite) 
    : ChessPiece(isWhite, L'P')
    {}
};