#pragma once

#include "BaseEdgeCell.h"

class BaseHorizontalEdgeCell : public BaseEdgeCell<5, 2>
{
protected:
    static inline constexpr int _HALF_WIDTH = WIDTH / 2;
    const wchar_t _MARKED_LETTER;

public:
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
protected:
    void DrawMarkedLetter() const;
};