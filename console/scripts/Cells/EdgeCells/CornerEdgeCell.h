#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class CornerEdgeCell : public BaseEdgeCell<CellsConfiguration::VERTICAL_EDGE_WIDTH, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
public:
    enum class Type{
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };
private:
    static constexpr std::size_t LAST_COL = WIDTH - 1;
    const Type CORNER_TYPE;
    const std::size_t FILLED_LINE;
public:
    CornerEdgeCell(wchar_t edgeChar, const RGB* cellColor, Type cornerType) : 
        BaseEdgeCell{edgeChar, cellColor}, 
        CORNER_TYPE{cornerType}, FILLED_LINE {CORNER_TYPE == Type::TOP_LEFT || CORNER_TYPE == Type::TOP_RIGHT ? HEIGHT - 1 : 0}
    {
    }

    CornerEdgeCell(wchar_t edgeChar, Type cornerType) : CornerEdgeCell{edgeChar, nullptr, cornerType}
    {
    }

    TextBlock BuildTextBlock(const RGB* textColor, const RGB* bgColor) const override
    {
        TextBlock textBlock{HEIGHT, textColor, bgColor, true};

        for (std::size_t i = 0; i < HEIGHT; ++i)
        {
            if (i == FILLED_LINE)
            {
                if (CORNER_TYPE == Type::TOP_LEFT || CORNER_TYPE == Type::BOTTOM_LEFT)
                {
                    AddOutsideLine(textBlock[i], {}, LAST_COL);
                    AddEdgeChars(textBlock[i], 1);     
                }
                else
                {
                    AddEdgeChars(textBlock[i], 1);
                    AddOutsideLine(textBlock[i], {}, LAST_COL);
                }
            }
            else
                AddOutsideLine(textBlock[i], {}, WIDTH);
        }

        return textBlock;
    }
};