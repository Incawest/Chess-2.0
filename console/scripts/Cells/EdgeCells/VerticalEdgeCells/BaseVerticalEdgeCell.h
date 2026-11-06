#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class BaseVerticalEdgeCell : public BaseEdgeCell<CellsConfiguration::VERTICAL_EDGE_WIDTH, CellsConfiguration::BASE_HEIGHT>
{
protected:
    static inline constexpr int _LAST_COL = WIDTH - 1;
    static inline constexpr int _NEXT_TO_LAST_COL = _LAST_COL - 1;
    static inline constexpr int _MID_HEIGHT = HEIGHT / 2;
    const int _MARKED_DIGIT;
    const std::function<void()> _DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC = [this](){
        Utilits::DrawEmptyLine(_LAST_COL);
    };
    const std::function<void()> _DRAW_LINE_BEYOND_CHESSBOARD_FUNC;
public:
    BaseVerticalEdgeCell(std::function<void()> drawLineBeyondChessboardFunc, wchar_t edgeChar, int markedDigit);
    BaseVerticalEdgeCell(std::function<void()> drawLineBeyondChessboardFunc, wchar_t edgeChar, int markedDigit, const RGB* cellColor);
};