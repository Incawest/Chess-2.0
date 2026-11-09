#pragma once

#include <iostream>

#include "BaseCell.h"
#include "Console.h"
#include "Utilits.h"

using Color = Console::Color;
using RGB = Console::RGB;

template<std::size_t width, std::size_t height>
requires(width >= 1 && height >= 1)
class BaseEdgeCell : public BaseCell<width, height>
{
protected:
    const wchar_t EDGE_CHAR;
public:
    BaseEdgeCell(wchar_t edgeChar, const RGB* cellColor) :  BaseCell<width, height>{cellColor}, EDGE_CHAR{edgeChar}
    {
    }

    explicit BaseEdgeCell(wchar_t edgeChar) : BaseEdgeCell{edgeChar, nullptr}
    {
    }
protected:
    void DrawOutsideLine(std::wstring_view line, std::size_t leftPadding, std::size_t rightPadding = 0) const
    {
        const RGB* previousBGColor = Console::GetBGColor();
        Console::ResetBGColor();
        Utilits::DrawEmptyLine(leftPadding);

        if (!line.empty())
        {
            const RGB* previousTextColor = Console::GetTextColor();
            Console::SetTextColor(this->_cellColor);
            std::wcout << line;
            Console::SetTextColor(previousTextColor);
        }

        Utilits::DrawEmptyLine(rightPadding);
        Console::SetBGColor(previousBGColor);
    }

    void DrawEdgeChars(std::size_t count) const
    {
        const RGB* previousColor = Console::GetTextColor();
        Console::SetTextColor(this->_cellColor);

        for (std::size_t i = 0; i < count; ++i)
            std::wcout << EDGE_CHAR;

        Console::SetTextColor(previousColor);
    }

};