#include "ChessPiece.h"

ChessPiece::MovePosition::MovePosition() noexcept = default;


ChessPiece::MovePosition::MovePosition(Vector2 position, bool isMoveForCapturingPieceOnly) noexcept : 
    _position{position}, _isMoveForCapturingPieceOnly{isMoveForCapturingPieceOnly}
{
}

Vector2 ChessPiece::MovePosition::GetPosition() const noexcept
{
    return _position;
}

bool ChessPiece::MovePosition::GetIsMoveForCapturingPieceOnly() const noexcept
{
    return _isMoveForCapturingPieceOnly;
}

ChessPiece::ChessPiece([[maybe_unused]] const ChessPiece::Key& constructorKey, wchar_t character, 
    bool isWhite, std::size_t pathsForMovesCount) : _character{character}, _isWhite{isWhite}
{
    if (isWhite == true) 
    {
        _pieceColor = _defaultPieceColor = &Color::WHITE;
    }
    else 
    {
        _pieceColor = _defaultPieceColor = &Color::BLACK;
    }

    _pathsForMoves.resize(pathsForMovesCount);
}

bool ChessPiece::GetIsWhite() const noexcept
{
    return _isWhite;
}

const TextBlock::RGB* ChessPiece::GetColor() const noexcept
{
    return _pieceColor;
}

Vector2 ChessPiece::GetPosition() const noexcept
{
    return _position;
}

std::size_t ChessPiece::GetCountOfFullPaths() const noexcept
{
    return _pathsForMoves.size();
}

std::span<const ChessPiece::MovePosition> ChessPiece::GetFullPathForMove(int pathForMoveIndex) const
{
    if (pathForMoveIndex < 0 || pathForMoveIndex >= _pathsForMoves.size())
        return {};
    else
        return _pathsForMoves[pathForMoveIndex];
}

void ChessPiece::SetIsCapturable(bool isCapturable)
{
    if (isCapturable)
    {
        _pieceColor = CAPTURABLE_PIECE_COLOR;
        Blinkable::PushUpdatingBlinkable(this);
    }
    else
    {
        _pieceColor = _defaultPieceColor;
        Blinkable::EraseUpdatingBlinkable(this);
    }

    _isCapturable = isCapturable;
}

void ChessPiece::SetPosition(Vector2 position) noexcept
{
    _position = position;
}

void ChessPiece::AddPiece(Line& line) const
{
    bool isSuccess = line.TrySetActiveColor(Line::ColorTarget::TEXT, _pieceColor);
    line += _character;

    if (isSuccess)
        line.SetActiveColorToDefault(Line::ColorTarget::TEXT);
}

void ChessPiece::Update()
{
    if (_isCapturable)
        _pieceColor = GetIsShining() ? CAPTURABLE_PIECE_COLOR : _defaultPieceColor ;
}