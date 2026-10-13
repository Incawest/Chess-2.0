#include "TopRightCornerEdgeCell.h"

TopRightCornerEdgeCell::TopRightCornerEdgeCell(wchar_t edgeChar) : 
    BaseCornerEdgeCell(edgeChar)
{
}

TopRightCornerEdgeCell::TopRightCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseCornerEdgeCell(edgeChar, cellColor)
{
}

void TopRightCornerEdgeCell::DrawCell(int line) const
{
    if (line == _LAST_LINE)
    {        
        DrawEdge();
        DrawEmptyLine(_LAST_COL);
    }
    else
        DrawEmptyLine(WIDTH);
}