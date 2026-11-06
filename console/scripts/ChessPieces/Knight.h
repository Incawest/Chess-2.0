#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, isWhite, L'k', 8}
    {}

private:
    void InitializePathsForMoves() override
    {  
        _pathsForMoves[0] = MovePosition{Vector2{-2, -1}, false};
        _pathsForMoves[1] = MovePosition{Vector2{-2, 1}, false};
        _pathsForMoves[2] = MovePosition{Vector2{-1, -2}, false};
        _pathsForMoves[3] = MovePosition{Vector2{-1, 2}, false};
        _pathsForMoves[4] = MovePosition{Vector2{1, -2}, false};
        _pathsForMoves[5] = MovePosition{Vector2{1, 2}, false};
        _pathsForMoves[6] = MovePosition{Vector2{2, -1}, false};
        _pathsForMoves[7] = MovePosition{Vector2{2, 1}, false};
    }
};