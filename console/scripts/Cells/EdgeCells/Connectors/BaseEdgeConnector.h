#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class BaseEdgeConnector : public BaseEdgeCell<CellsConfiguration::SPACE_BETWEEN_CELLS, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
protected:
    const std::function<void()> _DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC = [this]() { 
        Utilits::DrawEmptyLine(this->WIDTH);
    };
public:
    BaseEdgeConnector(wchar_t edgeChar);
    BaseEdgeConnector(wchar_t edgeChar, const RGB* cellColor);
};