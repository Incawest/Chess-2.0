#pragma once

#include "BaseVerticalEdgeCell.h"

class LeftVerticalEdgeCell : public BaseVerticalEdgeCell
{
public:
    LeftVerticalEdgeCell(wchar_t edgeChar, int markedDigit);
    LeftVerticalEdgeCell(wchar_t edgeChar, int markedDigit, const RGB* cellColor);
    void DrawCell(int line) const override;
};