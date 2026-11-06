#include "ChessPiece.h"

ChessPiece::MovePosition::MovePosition() noexcept = default;

ChessPiece::MovePosition::MovePosition(Vector2 position, bool isMoveForCapturingPieceOnly) noexcept : 
    ChessPiece::MovePosition::MovePosition{position, isMoveForCapturingPieceOnly, nullptr}
{
}

ChessPiece::MovePosition::MovePosition(Vector2 position, bool isMoveForCapturingPieceOnly, std::unique_ptr<MovePosition> nextPosInPath) noexcept : 
    _position{position}, _isMoveForCapturingPieceOnly{isMoveForCapturingPieceOnly}, nextPosInPath{std::move(nextPosInPath)}
{
}

Vector2 ChessPiece::MovePosition::GetPosition() const noexcept
{
    return _position;
}

bool ChessPiece::MovePosition::GetIsMoveForCapturingPieceOnly() const noexcept
{
    return nextPosInPath == nullptr && _isMoveForCapturingPieceOnly;
}

ChessPiece::ChessPiece( const ChessPiece::Key& constructorKey, bool isWhite, wchar_t character, std::size_t pathsForMovesCount) : 
_isWhite{isWhite}, _character{character}
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

ChessPiece::~ChessPiece() = default;


bool ChessPiece::GetIsWhite() const noexcept
{
    return _isWhite;
}

const RGB* ChessPiece::GetColor() const noexcept
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

std::vector<ChessPiece::MovePosition> ChessPiece::GetFullPathForMove(int pathForMoveIndex, Vector2 anchoredPosition) const
{
    if (pathForMoveIndex < 0 || pathForMoveIndex >= _pathsForMoves.size())
        return std::vector<ChessPiece::MovePosition>{};
    const ChessPiece::MovePosition* curMovePosition = &_pathsForMoves[pathForMoveIndex];
    std::vector<ChessPiece::MovePosition> fullPathForMove{};
    do
    {
        fullPathForMove.push_back(MovePosition{curMovePosition->GetPosition() + anchoredPosition, curMovePosition->GetIsMoveForCapturingPieceOnly()});
        curMovePosition = curMovePosition->nextPosInPath.get();
    } while (curMovePosition != nullptr);
    return fullPathForMove;
}

void ChessPiece::SetIsCapturable(bool isCapturable) noexcept
{
    if (isCapturable)
    {
        _pieceColor = _defaultPieceColor;
        Blinkable::PushUpdatingBlinkable(this);
    }
    else
    {
        _pieceColor = _CAPTURABLE_PIECE_COLOR;
        Blinkable::EraseUpdatingBlinkable(this);
    }

    _isCapturable = isCapturable;
}

void ChessPiece::SetPosition(Vector2 position) noexcept
{
    _position = position;
}

void ChessPiece::DrawPiece() const
{
    auto pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_pieceColor);
    std::wcout << _character;
    Console::SetTextColor(pastTextColor);
}

void ChessPiece::Update()
{
    if (_isCapturable)
        _pieceColor = GetIsShining() ? _CAPTURABLE_PIECE_COLOR : _defaultPieceColor ;
}