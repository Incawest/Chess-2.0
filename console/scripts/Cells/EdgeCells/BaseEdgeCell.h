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
    BaseEdgeCell(wchar_t edgeChar) : BaseEdgeCell(edgeChar, nullptr)
    {
    }
    BaseEdgeCell(wchar_t edgeChar, const RGB* cellColor) : BaseCell<width, height>(cellColor), _EDGE_CHAR{edgeChar}
    {
    }
protected:
    virtual void DrawEdge() const
    {
        auto pastTextColor = Console::GetTextColor();
        Console::SetTextColor(this->_cellColor);
        std::wcout << _EDGE_CHAR;
        Console::SetTextColor(pastTextColor);
    }
};