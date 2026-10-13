#pragma once

#include "BaseCornerEdgeCell.h"

class TopLeftCornerEdgeCell : public BaseCornerEdgeCell
{
private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
public:
    TopLeftCornerEdgeCell(wchar_t edgeChar);
    TopLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};