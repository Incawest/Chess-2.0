#pragma once

#include "BaseHorizontalEdgeCell.h"

class TopHorizontalEdgeCell : public BaseHorizontalEdgeCell
{
private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
    static inline constexpr const int _NEXT_TO_LAST_LINE = _LAST_LINE - 1;

public:
    TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
    void DrawCell(int line) const override;
};