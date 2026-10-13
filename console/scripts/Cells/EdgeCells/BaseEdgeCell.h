#pragma once

#include <iostream>
#include <vector>

#include "BaseCell.h"
#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

template<int width, int height>
requires(width > 0 && height > 0)
class BaseEdgeCell : public BaseCell<width, height>
{
protected:
    const wchar_t _EDGE_CHAR;

public:
    BaseEdgeCell(wchar_t edgeChar) : _EDGE_CHAR(edgeChar)
    {
    }
    BaseEdgeCell(wchar_t edgeChar, const RGB* cellColor) : BaseCell<width, height>(cellColor), _EDGE_CHAR{edgeChar}
    {
    }
protected:
    const RGB* SetConsoleTextColorAsCellColor() const
    {
        if (this->_cellColor != nullptr)
        {
            const RGB* pastTextColor = Console::GetTextColor();
            Console::SetTextColor(this->_cellColor);
            return pastTextColor;
        }
        else
            return nullptr;
    }

    void SetConsoleTextColorAsAnotherColor(const RGB* anotherColor) const
    {
        if (anotherColor != nullptr)
            Console::SetTextColor(anotherColor);
    }

    void DrawEdge() const
    {
        auto pastTextColor = SetConsoleTextColorAsCellColor();
        std::wcout << _EDGE_CHAR;
        SetConsoleTextColorAsAnotherColor(pastTextColor);
    }
};