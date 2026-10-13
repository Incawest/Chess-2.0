#pragma once

#include "BaseEdgeCell.h"

class BaseCornerEdgeCell : public BaseEdgeCell<2, 2>
{
protected:
    static inline constexpr int _LAST_COL = WIDTH - 1;
public:
    BaseCornerEdgeCell(wchar_t edgeChar);
    BaseCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
};