#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "BaseCell.h"
#include "Blinkable.h"
#include "CellsConfiguration.h"
#include "ChessPiece.h"
#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

class BaseBoardCell : 
    public BaseCell<CellsConfiguration::BASE_WIDTH, CellsConfiguration::BASE_HEIGHT>, public Blinkable
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

private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
    static inline constexpr int _HORIZONTAL_WIDTH = WIDTH - 2;
    static inline constexpr wchar_t _CHARACTER_MARK = L'*';
    bool _isSelected = false;
    bool _isMarked = false;
    
    std::weak_ptr<ChessPiece> _piece;

public:
    BaseBoardCell();
    BaseBoardCell(const RGB* cellColor);
    BaseBoardCell(const RGB* cellColor, std::weak_ptr<ChessPiece> piece);
    std::shared_ptr<ChessPiece> GetChessPiece() const noexcept;
    void SetSelection(bool isSelected) override;
    void SetMark(bool isMakred);
    void SetPieceOnCell(std::weak_ptr<ChessPiece> piece) noexcept;
    void DrawCell(int line) const override;

    void Update() override;
};