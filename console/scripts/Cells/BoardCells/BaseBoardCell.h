#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "BaseCell.h"
#include "CellsConfiguration.h"
#include "ChessPiece.h"
#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

class BaseBoardCell : public BaseCell<CellsConfiguration::BASE_WIDTH, CellsConfiguration::BASE_HEIGHT>
{
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

    static inline constexpr int _LAST_LINE = HEIGHT - 1;
    static inline constexpr int _HORIZONTAL_WIDTH = WIDTH - 2;

    std::weak_ptr<ChessPiece> _piece;
    const RGB* _cellColor = nullptr;

public:
    BaseBoardCell();
    BaseBoardCell(const RGB* cellColor);
    BaseBoardCell(
        const RGB* cellColor,
        std::weak_ptr<ChessPiece> piece
    );
    const RGB* GetPieceColor() const;
    const RGB* GetCellColor() const;
    void SetPieceOnCell(
        std::weak_ptr<ChessPiece> piece
    );
    virtual void DrawCell(int line) const override;
};