#pragma once

#include "BaseVerticalEdgeCell.h"

class RightVerticalEdgeCell : public BaseVerticalEdgeCell
{
public:
    RightVerticalEdgeCell(wchar_t edgeChar, int markedDigit);
    RightVerticalEdgeCell(wchar_t edgeChar, int markedDigit, const RGB* cellColor);
    void DrawCell(int line) const override;
};