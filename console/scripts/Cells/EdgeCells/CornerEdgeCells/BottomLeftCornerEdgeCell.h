#pragma once

#include "BaseCornerEdgeCell.h"

class BottomLeftCornerEdgeCell : public BaseCornerEdgeCell
{
public:
    using BaseCornerEdgeCell::BaseCornerEdgeCell;
    void DrawCell(int line) const override;
};