#pragma once

#include "BaseVerticalEdgeCell.h"

class LeftVerticalEdgeCell : public BaseVerticalEdgeCell
{
public:
    LeftVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit);
    LeftVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor);
    void DrawCell(int line) const override;
protected:
    virtual void DrawMarkedDigitAndEdge() const override;
};