#include "BottomLeftCornerEdgeCell.h"

BottomLeftCornerEdgeCell::BottomLeftCornerEdgeCell(wchar_t edgeChar) : 
    BaseCornerEdgeCell(edgeChar)
{
}

BottomLeftCornerEdgeCell::BottomLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseCornerEdgeCell(edgeChar, cellColor)
{
}

void BottomLeftCornerEdgeCell::DrawCell(int line) const
{
    if (line == 0)
    {
        DrawEmptyLine(_LAST_COL);
        DrawEdge();
    }
    else
        DrawEmptyLine(WIDTH);
}