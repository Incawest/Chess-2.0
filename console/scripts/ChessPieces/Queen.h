#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, isWhite, L'Q', 8}
    {}

private:
    void InitializePathsForMoves() override
    {
        _pathsForMoves[0] = MovePosition{Vector2{-1, -1}, false};
        _pathsForMoves[1] = MovePosition{Vector2{-1, 0}, false};
        _pathsForMoves[2] = MovePosition{Vector2{-1, 1}, false};
        _pathsForMoves[3] = MovePosition{Vector2{0, -1}, false};
        _pathsForMoves[4] = MovePosition{Vector2{0, 1}, false};
        _pathsForMoves[5] = MovePosition{Vector2{1, -1}, false};
        _pathsForMoves[6] = MovePosition{Vector2{1, 0}, false};
        _pathsForMoves[7] = MovePosition{Vector2{1, 1}, false};

        std::array<std::unique_ptr<ChessPiece::MovePosition>, 8> endsOfPaths;
        std::array<ChessPiece::MovePosition*, endsOfPaths.size()> _currentMovePositionsInPath;

        for (std::size_t i = 0; i < endsOfPaths.size(); ++i)
            _currentMovePositionsInPath[i] = &_pathsForMoves[i];

        for (int i = 2; i <= 8; ++i)
        {
            endsOfPaths = {
                std::make_unique<ChessPiece::MovePosition>(Vector2{-i, -i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{-i, 0}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{-i, i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{0, -i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{0, i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{i, -i}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{i, 0}, false),
                std::make_unique<ChessPiece::MovePosition>(Vector2{i, i}, false)
            };
            
            for (std::size_t j = 0; j < endsOfPaths.size(); ++j)
            {
                _currentMovePositionsInPath[j]->nextPosInPath = std::move(endsOfPaths[j]);
                _currentMovePositionsInPath[j] = _currentMovePositionsInPath[j]->nextPosInPath.get();
            }
        }
    }
};