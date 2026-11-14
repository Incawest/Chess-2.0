#pragma once

#include <iostream>

#include "BaseCell.h"
#include "Utilits.h"

template<std::size_t width, std::size_t height>
requires(width >= 1 && height >= 1)
class BaseEdgeCell : public BaseCell<width, height>
{
protected:
    using BaseCell = BaseCell<width, height>;
    using RGB = typename BaseCell::RGB;
    using Color = typename BaseCell::Color;
    using Line = typename BaseCell::Line;
protected:
    const wchar_t EDGE_CHAR;
public:
    BaseEdgeCell(wchar_t edgeChar, const RGB* cellColor) :  BaseCell{cellColor}, EDGE_CHAR{edgeChar}
    {
    }

    explicit BaseEdgeCell(wchar_t edgeChar) : BaseEdgeCell{edgeChar, nullptr}
    {
    }
protected:
    void AddOutsideLine(
        Line& processingLine, 
        std::wstring_view outsideLine, 
        std::size_t leftPadding = 0, 
        std::size_t rightPadding = 0
    ) const
    {
        processingLine.ResetActiveColor(Line::ColorTarget::BACKGROUND);
        processingLine.AddChars(leftPadding);

        if (!outsideLine.empty())
        {
            bool isSuccess = processingLine.TrySetActiveColor(Line::ColorTarget::TEXT, this->_cellColor);
            processingLine += outsideLine;
            if (isSuccess)
                processingLine.SetActiveColorToDefault(Line::ColorTarget::TEXT);
        }

        processingLine.AddChars(rightPadding);
        processingLine.SetActiveColorToDefault(Line::ColorTarget::BACKGROUND);
    }

    void AddEdgeChars(Line& line, std::size_t charsCount) const
    {
        bool isSuccess = line.TrySetActiveColor(Line::ColorTarget::TEXT, this->_cellColor);

        for (std::size_t i = 0; i < charsCount; ++i)
            line += EDGE_CHAR;

        if (isSuccess)
            line.SetActiveColorToDefault(Line::ColorTarget::TEXT);
    }
};