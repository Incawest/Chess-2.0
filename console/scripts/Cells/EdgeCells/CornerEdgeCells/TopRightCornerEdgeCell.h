#pragma once

#include "BaseCornerEdgeCell.h"

class TopRightCornerEdgeCell : public BaseCornerEdgeCell
{
private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
public:
    TopRightCornerEdgeCell(wchar_t edgeChar);
    TopRightCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};