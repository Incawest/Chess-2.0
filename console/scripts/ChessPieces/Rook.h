#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, L'R', isWhite, 4}
    {
    }

protected:
    void InitializePathsForMoves() override
    {
        for (int i = 1; i <= 8; ++i)
        {
            _pathsForMoves[0].push_back(MovePosition{Vector2{-i, 0}, false});
            _pathsForMoves[1].push_back(MovePosition{Vector2{0, -i}, false});
            _pathsForMoves[2].push_back(MovePosition{Vector2{0, i}, false});
            _pathsForMoves[3].push_back(MovePosition{Vector2{i, 0}, false});
        }
    }
};