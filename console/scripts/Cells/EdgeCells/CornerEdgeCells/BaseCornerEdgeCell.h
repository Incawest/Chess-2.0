#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class BaseCornerEdgeCell : public BaseEdgeCell<CellsConfiguration::VERTICAL_EDGE_WIDTH, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
protected:
    static inline constexpr int _LAST_COL = WIDTH - 1;
    const std::function<void()> _DRAW_FULL_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC = [this](){
        Utilits::DrawEmptyLine(this->WIDTH);
    };
    const std::function<void()> _DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC = [this](){
        Utilits::DrawEmptyLine(this->_LAST_COL);
    };
public:
    using BaseEdgeCell::BaseEdgeCell;
};