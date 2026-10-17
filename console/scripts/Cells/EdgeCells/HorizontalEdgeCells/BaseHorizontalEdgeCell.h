#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"

class BaseHorizontalEdgeCell : public BaseEdgeCell<CellsConfiguration::BASE_WIDTH, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
protected:
    static inline constexpr int _HALF_WIDTH = WIDTH / 2;
    const wchar_t _MARKED_LETTER;
    const std::function<void()> _DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC = [this](){
        DrawEmptyLine(WIDTH);
    };
    const std::function<void()> _DRAW_LINE_BEYOND_CHESSBOARD_FUNC = [this](){
        DrawEmptyLine(_HALF_WIDTH);
        DrawMarkedLetter();
        DrawEmptyLine(_HALF_WIDTH);
    };

public:
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
protected:
    void DrawMarkedLetter() const;
};