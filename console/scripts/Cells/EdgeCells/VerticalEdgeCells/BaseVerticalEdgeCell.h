#pragma once

#include "BaseEdgeCell.h"

class BaseVerticalEdgeCell : public BaseEdgeCell<2, 3>
{
protected:
    static inline constexpr int _LAST_COL = WIDTH - 1;
    static inline constexpr int _NEXT_TO_LAST_COL = _LAST_COL - 1;
    static inline constexpr int _MID_HEIGHT = HEIGHT / 2;
    const wchar_t _MARKED_DIGIT;

public:
    BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit);
    BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor);
protected:
    virtual void DrawMarkedDigitAndEdge() const = 0;
};