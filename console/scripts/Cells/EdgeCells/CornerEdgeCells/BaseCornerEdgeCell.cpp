#include "BaseCornerEdgeCell.h"

BaseCornerEdgeCell::BaseCornerEdgeCell(wchar_t edgeChar) : 
    BaseEdgeCell(2, 2, edgeChar), _LAST_COL{WIDTH - 1}
{
}

BaseCornerEdgeCell::BaseCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseEdgeCell(2, 2, edgeChar, cellColor), _LAST_COL{WIDTH - 1}
{
}