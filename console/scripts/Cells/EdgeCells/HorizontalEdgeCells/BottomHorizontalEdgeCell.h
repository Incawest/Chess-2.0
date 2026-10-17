#pragma once

#include "BaseHorizontalEdgeCell.h"

class BottomHorizontalEdgeCell : public BaseHorizontalEdgeCell
{
public:
    using BaseHorizontalEdgeCell::BaseHorizontalEdgeCell;
    void DrawCell(int line) const override;
};