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
    std::shared_ptr<BaseChessboard> _chessboard;
    std::vector<std::shared_ptr<ChessPiece>> _chessPieces;
    int _selectedPieceIndex = -1;

public:
    Player(std::shared_ptr<BaseChessboard> chessboard, bool isOnWhiteTeam);
    void ActivateSelection();
    void GoToNextSelection(Utilits::DeltaMove direction);
    void DeactivateSelection();

private:
    void SetDefaultChessPiecesSetup(bool isOnWhiteTeam);
};