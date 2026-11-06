#include "Player.h"

Player::Player(std::weak_ptr<BaseChessboard> chessboard, bool isOnWhiteTeam) : _chessboard{chessboard} 
{
    SetDefaultChessPiecesSetup(isOnWhiteTeam);
}

void Player::ActivateSelection()
{
    if (_chessPieces.size() == 0)
        return;
    
    _selectedPieceIndex = 0;
    Utilits::GetSharedPtr(_chessboard)->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());
}

void Player::GoToNextSelection(bool toGoForward)
{
    int piecesCount = _chessPieces.size();

    if(piecesCount <= 0)
        return;

    int delta = toGoForward ? 1 : -1;
    _selectedPieceIndex += delta;
    if (_selectedPieceIndex == piecesCount)
        _selectedPieceIndex = 0;
    else if (_selectedPieceIndex < 0)
        _selectedPieceIndex = piecesCount - 1;
    Utilits::GetSharedPtr(_chessboard)->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());
}

bool Player::FixSelection()
{
    auto chessboard = Utilits::GetSharedPtr(_chessboard);
    chessboard->CalculateAllowedMoves();
    return chessboard->GetAllowedMovesCount() > 0;
}

void Player::UnfixSelection()
{
    Utilits::GetSharedPtr(_chessboard)->ClearAllowedMoves();
}

void Player::DeactivateSelection()
{
    _selectedPieceIndex = -1;
    Utilits::GetSharedPtr(_chessboard)->SetSelectedCell(Vector2{-1, -1});
}

void Player::GoToNextPathForMove(BaseChessboard::DeltaMove direction)
{
    Utilits::GetSharedPtr(_chessboard)->SetNextMarkedCell(direction);
}

void Player::SetDefaultChessPiecesSetup(bool isOnWhiteTeam)
{
    auto realChessboard = Utilits::GetSharedPtr(_chessboard);
    int rowOffset, offsetCoeff;
    int chessBoardSize = realChessboard->GetChessboardSize();
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
        realChessboard->SetPieceOnCell(_chessPieces[i], piecePosition);
    }
    
    piecePosition.row += offsetCoeff;
    for (int i = 8; i < _chessPieces.size(); ++i)
    {
        piecePosition.col = i - 8;
        _chessPieces[i] = ChessPiece::InitializeSharedChessPiece<Queen>(isOnWhiteTeam);
        realChessboard->SetPieceOnCell(_chessPieces[i], piecePosition);
    }
}