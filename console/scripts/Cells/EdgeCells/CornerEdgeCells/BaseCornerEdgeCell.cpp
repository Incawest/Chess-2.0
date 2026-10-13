#include "BaseCornerEdgeCell.h"

BaseCornerEdgeCell::BaseCornerEdgeCell(wchar_t edgeChar) : 
    BaseEdgeCell(edgeChar)
{
}

BaseCornerEdgeCell::BaseCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseEdgeCell(edgeChar, cellColor)
{
}