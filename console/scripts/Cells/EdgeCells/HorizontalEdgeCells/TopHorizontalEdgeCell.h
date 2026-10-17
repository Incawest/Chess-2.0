#pragma once

#include "BaseHorizontalEdgeCell.h"

class TopHorizontalEdgeCell : public BaseHorizontalEdgeCell
{
private:
    static inline constexpr int _LAST_LINE = HEIGHT - 1;
    static inline constexpr const int _NEXT_TO_LAST_LINE = _LAST_LINE - 1;

public:
    using BaseHorizontalEdgeCell::BaseHorizontalEdgeCell;
    void DrawCell(int line) const override;
};