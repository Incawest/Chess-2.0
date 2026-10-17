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
    const Console::RGB* _cellColor;
    
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
        for (std::size_t i = 0; i < length; ++i)
            std::wcout << L' ';
    }

    void DrawLineBeyondChessboard(const std::function<void()>& drawLineFunction) const
    {
        const Console::RGB* pastBgColor = Console::GetBGColor();
        Console::ResetBGColor();
        if(drawLineFunction != nullptr)
            drawLineFunction();
        Console::SetBGColor(pastBgColor);
    }
};