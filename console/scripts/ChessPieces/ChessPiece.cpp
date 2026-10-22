#include "ChessPiece.h"

ChessPiece::ChessPiece(
    bool isWhite, 
    wchar_t character
) : _isWhite{isWhite}, _character{character}
{
    if (isWhite == true) 
    {
        _figureColor = &Color::WHITE;
    }
    else 
    {
        _figureColor = &Color::BLACK;
    }
}

ChessPiece::~ChessPiece() = default;

wchar_t ChessPiece::GetCharacter() const noexcept
{
    return _character;
}

bool ChessPiece::GetIsWhite() const noexcept
{
    return _isWhite;
}

const RGB* ChessPiece::GetColor() const noexcept
{
    return _figureColor;
}

void ChessPiece::SetPosition(int col, int row) noexcept
{
    _positionCol = col;
    _positionRow = row;
}

void ChessPiece::DrawPiece() const
{
    auto pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_figureColor);
    std::wcout << L' ' << _character << L' ';
    Console::SetTextColor(pastTextColor);
}

