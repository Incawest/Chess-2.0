#include "Player.h"

Player::Player(std::shared_ptr<BaseChessboard> chessboard, bool isOnWhiteTeam) : _chessboard{chessboard} 
{
    SetDefaultChessPiecesSetup(isOnWhiteTeam);
}

void Player::ActivateSelection()
{
    if (_chessPieces.size() == 0)
        return;
    
    _selectedPieceIndex = 0;
    _chessboard->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());
}

void Player::GoToNextSelection(Utilits::DeltaMove direction)
{
    if(_selectedPieceIndex < 0 || static_cast<std::size_t>(_selectedPieceIndex) >= _chessPieces.size())
        return;

    int nextIndex = Utilits::FindNextPositionIndex(_chessPieces, _chessPieces[_selectedPieceIndex]->GetPosition(), direction, 
        _chessboard->CHESSBOARD_SIZE, [](const auto& piece){
            return piece->GetPosition();
    });
        
    if (nextIndex >= 0)
    {
        _selectedPieceIndex = nextIndex;
        _chessboard->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());   
    }
}

void Player::DeactivateSelection()
{
    _selectedPieceIndex = -1;
    _chessboard->SetSelectedCell(Vector2{-1, -1});
}

void Player::SetDefaultChessPiecesSetup(bool isOnWhiteTeam)
{
    int rowOffset, offsetCoeff;
    int chessBoardSize = _chessboard->GetChessboardSize();
    if (isOnWhiteTeam)
    {
        rowOffset = chessBoardSize - 1;
        offsetCoeff = -1;
    }
    else
    {
        rowOffset = 0;
        offsetCoeff = 1;
    }
    _chessPieces.resize(16);
    _chessPieces[0] = ChessPiece::InitializeSharedChessPiece<Rook>(isOnWhiteTeam);
    _chessPieces[1] = ChessPiece::InitializeSharedChessPiece<Knight>(isOnWhiteTeam);
    _chessPieces[2] = ChessPiece::InitializeSharedChessPiece<Bishop>(isOnWhiteTeam);
    _chessPieces[3] = ChessPiece::InitializeSharedChessPiece<Queen>(isOnWhiteTeam);
    _chessPieces[4] = ChessPiece::InitializeSharedChessPiece<King>(isOnWhiteTeam);
    _chessPieces[5] = ChessPiece::InitializeSharedChessPiece<Bishop>(isOnWhiteTeam);
    _chessPieces[6] = ChessPiece::InitializeSharedChessPiece<Knight>(isOnWhiteTeam);
    _chessPieces[7] = ChessPiece::InitializeSharedChessPiece<Rook>(isOnWhiteTeam);

    Vector2 piecePosition = Vector2{rowOffset, 0};
    for (int i = 0; i < chessBoardSize; ++i)
    {
        piecePosition.col = i;
        _chessboard->SetPieceOnCell(_chessPieces[i], piecePosition);
    }
    
    piecePosition.row += offsetCoeff;
    for (int i = 8; i < _chessPieces.size(); ++i)
    {
        piecePosition.col = i - 8;
        _chessPieces[i] = ChessPiece::InitializeSharedChessPiece<Queen>(isOnWhiteTeam);
        _chessboard->SetPieceOnCell(_chessPieces[i], piecePosition);
    }
}