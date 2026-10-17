#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"

class BaseEdgeConnector : public BaseEdgeCell<CellsConfiguration::SPACE_BETWEEN_CELLS, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
protected:
    const std::function<void()> _DRAW_EMPTY_LINE_BEYOND_CHESSBOARD = [this]() { 
        this->DrawEmptyLine(this->WIDTH);
    };
public:
    using BaseEdgeCell::BaseEdgeCell;
};