#include "TopLeftCornerEdgeCell.h"

TopLeftCornerEdgeCell::TopLeftCornerEdgeCell(wchar_t edgeChar) : 
    BaseCornerEdgeCell(edgeChar), _LAST_LINE{HEIGHT - 1}
{
}

TopLeftCornerEdgeCell::TopLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseCornerEdgeCell(edgeChar, cellColor), _LAST_LINE{HEIGHT - 1}
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