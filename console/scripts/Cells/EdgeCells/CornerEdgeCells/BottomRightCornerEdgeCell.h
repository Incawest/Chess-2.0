#pragma once

#include "BaseCornerEdgeCell.h"

class BottomRightCornerEdgeCell : public BaseCornerEdgeCell
{
public:
    using BaseCornerEdgeCell::BaseCornerEdgeCell;
    void DrawCell(int line) const override;
};