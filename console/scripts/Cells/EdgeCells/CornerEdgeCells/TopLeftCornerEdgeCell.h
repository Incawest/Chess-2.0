#pragma once

#include "BaseCornerEdgeCell.h"

class TopLeftCornerEdgeCell : public BaseCornerEdgeCell
{
private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
public:
    using BaseCornerEdgeCell::BaseCornerEdgeCell;
    void DrawCell(int line) const override;
};