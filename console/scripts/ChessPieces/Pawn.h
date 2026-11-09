#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
// private:
//     int _teamFactor;
public:
    Pawn(const Key& constructorKey, bool isWhite) 
    : ChessPiece{constructorKey, L'P', isWhite, 3}//, _teamFactor{isWhite ? 1 : -1}
    {
    }

protected:
    void InitializePathsForMoves() override
    {
        _pathsForMoves[0] = {MovePosition{Vector2{-1, -1}, true}};
        _pathsForMoves[1] = {MovePosition{Vector2{-1, 0}, false}, MovePosition{Vector2{-2, 0}, false}};
        _pathsForMoves[2] = {MovePosition{Vector2{-1, 1}, true}};
    }
};