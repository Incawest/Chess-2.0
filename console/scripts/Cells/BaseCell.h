#pragma once

#include <functional>
#include <iostream>

#include "Console.h"

template<int width, int height>
requires(width > 0 && height > 0)
class BaseCell
{
public:
    static inline constexpr int WIDTH = width;
    static inline constexpr int HEIGHT = height;

protected:
    static inline const Console::RGB* const _SELECTED_CELL_COLOR = &Console::Color::YELLOW;
    const Console::RGB* _cellColor;
    const Console::RGB* _unselectedCellColor;

public:
    BaseCell() noexcept : BaseCell{nullptr}
    {
    }
    
    BaseCell(const Console::RGB* cellColor) noexcept : _unselectedCellColor{cellColor} 
    {
        SetSelection(false);
    }
    
    virtual ~BaseCell() = default;

    void SetCellColor(const Console::RGB* cellColor) noexcept
    {
        _unselectedCellColor = cellColor;
    }

    virtual void SetSelection(bool isSelected)
    {
        _cellColor = isSelected ? _SELECTED_CELL_COLOR : _unselectedCellColor;
    }

    virtual void DrawCell(int line) const = 0;
};