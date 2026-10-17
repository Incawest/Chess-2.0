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
    const std::function<void()> _DRAW_EDGE_CHARS_FUNC;
public:
    BaseEdgeCell(wchar_t edgeChar) : BaseEdgeCell(edgeChar, nullptr)
    {
    }
    BaseEdgeCell(wchar_t edgeChar, const RGB* cellColor) : BaseEdgeCell([this](){
            std::wcout << _EDGE_CHAR;
        }, edgeChar, cellColor)
    {
    }
    BaseEdgeCell(std::function<void()> drawEdgeCharsFunc, wchar_t edgeChar) : BaseEdgeCell(drawEdgeCharsFunc, edgeChar, nullptr)
    {
    }
    BaseEdgeCell(std::function<void()> drawEdgeCharsFunc, wchar_t edgeChar, const RGB* cellColor) : 
        BaseCell<width, height>(cellColor), _DRAW_EDGE_CHARS_FUNC{drawEdgeCharsFunc}, _EDGE_CHAR{edgeChar}
    {
    }
protected:
    void DrawEdge(const std::function<void()>& drawEdgeCharsFunc) const
    {
        auto pastTextColor = Console::GetTextColor();
        Console::SetTextColor(this->_cellColor);
        if (drawEdgeCharsFunc != nullptr)
            drawEdgeCharsFunc();
        Console::SetTextColor(pastTextColor);
    }
};