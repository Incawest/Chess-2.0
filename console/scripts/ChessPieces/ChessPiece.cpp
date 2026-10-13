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

wchar_t ChessPiece::GetCharacter() const
{
    return _character;
}

bool ChessPiece::GetIsWhite() const
{
    return _isWhite;
}

const RGB* ChessPiece::GetColor() const
{
    return _figureColor;
}

void ChessPiece::SetPosition(int col, int row)
{
    _positionCol = col;
    _positionRow = row;
}

void ChessPiece::DrawPiece() const
{
    Console::SetTextColor(_figureColor);
    std::wcout << L' ' << _character << L' ';
}

