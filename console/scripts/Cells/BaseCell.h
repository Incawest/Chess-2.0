#pragma once

#include "Console.h"

template<int width, int height>
requires(width > 0 && height > 0)
class BaseCell
{
public:
    static inline constexpr int WIDTH = width;
    static inline constexpr int HEIGHT = height;
protected:
    const Console::RGB* _cellColor = nullptr;
    
public:
    BaseCell() = default;
    
    BaseCell(const Console::RGB* cellColor) : _cellColor{cellColor}
    {
    }
    
    virtual ~BaseCell() = default;

    void SetCellColor(const Console::RGB* cellColor)
    {
        _cellColor = cellColor;
    }

    virtual void DrawCell(int line) const = 0;

protected:
    void DrawEmptyLine(int length) const
    {
        if (length == 0)
            return;
        std::wcout << std::wstring(length, L' ');
    }
};