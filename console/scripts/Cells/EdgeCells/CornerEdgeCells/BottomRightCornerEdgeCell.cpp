#include "BottomRightCornerEdgeCell.h"

BottomRightCornerEdgeCell::BottomRightCornerEdgeCell(wchar_t edgeChar) : 
    BaseCornerEdgeCell(edgeChar)
{
}

BottomRightCornerEdgeCell::BottomRightCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor) : 
    BaseCornerEdgeCell(edgeChar, cellColor)
{
}

void BottomRightCornerEdgeCell::DrawCell(int line) const
{
    if (line == 0)
    {
        DrawEdge();
        DrawEmptyLine(_LAST_COL);
    }
    else
        DrawEmptyLine(WIDTH);
}