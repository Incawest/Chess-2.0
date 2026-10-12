#include "BottomHorizontalEdgeCell.h"

BottomHorizontalEdgeCell::BottomHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseHorizontalEdgeCell(edgeChar, markedLetter)
{
}

BottomHorizontalEdgeCell::BottomHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseHorizontalEdgeCell(edgeChar, markedLetter, cellColor)
{
}

void BottomHorizontalEdgeCell::DrawCell(int line) const
{
    if (line == 0)
    {
        DrawEmptyLine(_HALF_WIDTH);
        DrawEdge();
        DrawEmptyLine(_HALF_WIDTH);
    }
    else if (line == 1)
    {
        DrawEmptyLine(_HALF_WIDTH);
        DrawMarkedLetter();
        DrawEmptyLine(_HALF_WIDTH);
    }
    else
        DrawEmptyLine(WIDTH);
}