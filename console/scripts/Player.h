#pragma once

#include <memory>
#include <vector>

#include "AllChessPieces.h"
#include "BaseChessboard.h"
#include "ChessPiece.h"
#include "Utilits.h"

class Player
{
private:
    std::weak_ptr<BaseChessboard> _chessboard;
    std::vector<std::shared_ptr<ChessPiece>> _chessPieces;
    int _selectedPieceIndex = -1;

public:
    Player(std::weak_ptr<BaseChessboard> chessboard, bool isOnWhiteTeam);
    void ActivateSelection();
    void GoToNextSelection(bool toGoForward);
    bool FixSelection();
    void UnfixSelection();
    void DeactivateSelection();

    void GoToNextPathForMove(BaseChessboard::DeltaMove direction);
private:
    void SetDefaultChessPiecesSetup(bool isOnWhiteTeam);
};