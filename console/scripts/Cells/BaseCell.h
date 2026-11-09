#pragma once

#include <functional>
#include <iostream>

#include "Console.h"

template<std::size_t width, std::size_t height>
requires(width >= 1 && height >= 1)
class BaseCell
{
public:
    static constexpr std::size_t WIDTH = width;
    static constexpr std::size_t HEIGHT = height;

protected:
    static constexpr const Console::RGB* SELECTED_CELL_COLOR = &Console::Color::YELLOW;
    const Console::RGB* _cellColor;

private:
    const Console::RGB* _unselectedCellColor;

public:
    explicit BaseCell(const Console::RGB* cellColor) noexcept : _unselectedCellColor{cellColor} 
    {
        SetSelection(false);
    }

    BaseCell() noexcept : BaseCell{nullptr}
    {
    }
    
    virtual ~BaseCell() = default;

    void SetCellColor(const Console::RGB* cellColor) noexcept
    {
        _unselectedCellColor = cellColor;
    }

    virtual void SetSelection(bool isSelected)
    {
        _cellColor = isSelected ? SELECTED_CELL_COLOR : _unselectedCellColor;
    }

    virtual void DrawCell(std::size_t line) const = 0;
};