#pragma once

#include "BaseHorizontalEdgeCell.h"

class BottomHorizontalEdgeCell : public BaseHorizontalEdgeCell
{
public:
    BottomHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    BottomHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
    void DrawCell(int line) const override;
};