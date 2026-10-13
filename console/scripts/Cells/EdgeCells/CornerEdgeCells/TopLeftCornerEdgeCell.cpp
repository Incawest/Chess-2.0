#include "TopLeftCornerEdgeCell.h"

TopLeftCornerEdgeCell::TopLeftCornerEdgeCell(wchar_t edgeChar) : 
    BaseCornerEdgeCell(edgeChar)
{
}

TopLeftCornerEdgeCell::TopLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseCornerEdgeCell(edgeChar, cellColor)
{
}

void TopLeftCornerEdgeCell::DrawCell(int line) const
{
    if (line == _LAST_LINE)
    {
        DrawEmptyLine(_LAST_COL);
        DrawEdge();
    }
    else
        DrawEmptyLine(WIDTH);
}