#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, isWhite, L'R', 4}
    {
    }

protected:
    void InitializePathsForMoves() override
    {
        _pathsForMoves[0] = MovePosition{Vector2{-1, 0}, false};
        _pathsForMoves[1] = MovePosition{Vector2{0, -1}, false};
        _pathsForMoves[2] = MovePosition{Vector2{0, 1}, false};
        _pathsForMoves[3] = MovePosition{Vector2{1, 0}, false};
        std::array<std::unique_ptr<ChessPiece::MovePosition>, 4> endsOfPaths;
        std::array<ChessPiece::MovePosition*, endsOfPaths.size()> _currentMovePositionsInPath;

        for (std::size_t i = 0; i < endsOfPaths.size(); ++i)
            _currentMovePositionsInPath[i] = &_pathsForMoves[i];

        for (int i = 2; i <= 8; ++i)
        {
            endsOfPaths = {
                std::make_unique<ChessPiece::MovePosition>(Vector2{-i, 0}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{0, -i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{0, i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{i, 0}, false)
            };
            
            for (std::size_t j = 0; j < endsOfPaths.size(); ++j)
            {
                _currentMovePositionsInPath[j]->nextPosInPath = std::move(endsOfPaths[j]);
                _currentMovePositionsInPath[j] = _currentMovePositionsInPath[j]->nextPosInPath.get();
            }
        }
    }
};