#pragma once

#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

class ChessPiece
{
private:
    bool _isAlive = true;

protected:
    const RGB* _figureColor;
    wchar_t _character;
    bool _isWhite;
    int _positionCol;
    int _positionRow;
    
public:
    ChessPiece(
        bool _isWhite,
        wchar_t _type
    );

    virtual ~ChessPiece() = 0;
    
    wchar_t GetCharacter() const;
    bool GetIsWhite() const;
    const RGB* GetColor() const;
    void SetPosition(int col, int row);
    void DrawPiece() const;
};