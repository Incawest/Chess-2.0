#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class VerticalEdgeCell : public BaseEdgeCell<CellsConfiguration::VERTICAL_EDGE_WIDTH, CellsConfiguration::BASE_HEIGHT>
{
    static_assert(WIDTH >= 2);
public:
    enum class Type
    {
        LEFT,
        RIGHT
    };
protected:
    static constexpr std::size_t LAST_COL = WIDTH - 1;
    static constexpr std::size_t MID_HEIGHT = HEIGHT / 2;
    const std::wstring MARKED_DIGIT;
    const std::size_t LAST_COL_TO_MARKED_ONE;
    const Type SIDE_TYPE;
public:
    VerticalEdgeCell(wchar_t edgeChar, std::size_t markedDigit, const RGB* cellColor, Type sideType) :
        BaseEdgeCell{edgeChar, cellColor}, MARKED_DIGIT{std::to_wstring(markedDigit)}, 
        LAST_COL_TO_MARKED_ONE{LAST_COL - MARKED_DIGIT.size()}, SIDE_TYPE{sideType}
    {
    }

    VerticalEdgeCell(wchar_t edgeChar, std::size_t markedDigit, Type sideType) : 
        VerticalEdgeCell{edgeChar, markedDigit, nullptr, sideType}
    {
    }

    void DrawCell(std::size_t line) const override
    {
        if (SIDE_TYPE == Type::LEFT)
        {
            if (line == MID_HEIGHT)
                DrawOutsideLine(MARKED_DIGIT, LAST_COL_TO_MARKED_ONE);
            else
                DrawOutsideLine({}, LAST_COL);
            DrawEdgeChars(1);
        }
        else
        {
            DrawEdgeChars(1);
            if (line == MID_HEIGHT)
                DrawOutsideLine(MARKED_DIGIT, 0, LAST_COL_TO_MARKED_ONE);
            else
                DrawOutsideLine({}, LAST_COL);
        }
    }
};