#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ChessPiece.h"
#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

class BaseBoardCell
{
private:
    std::weak_ptr<ChessPiece> _piece;
    const RGB* _cellColor = nullptr;

public:
    static inline constexpr int WIDTH = 5;  
    static inline constexpr int HEIGHT = 3;

private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
    static inline constexpr int _HORIZONTAL_WIDTH = WIDTH - 2;

public:
    BaseBoardCell();
    BaseBoardCell(const RGB* cellColor);
    BaseBoardCell(
        const RGB* cellColor,
        std::weak_ptr<ChessPiece> piece
    );
    void DrawCell(int line) const;
    void SetPieceOnCell(
        std::weak_ptr<ChessPiece> piece
    );
    const RGB* GetPieceColor() const;
    const RGB* GetCellColor() const;

private:
    struct CellboardParts final
    {
        static inline constexpr wchar_t HORIZONTAL_BORDER = L'\u2500';
        static inline constexpr wchar_t VERTICAL_BORDER = L'\u2502';
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u250C';
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u2510';
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2514';
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u2518';

        virtual ~CellboardParts() = 0;
    };
};