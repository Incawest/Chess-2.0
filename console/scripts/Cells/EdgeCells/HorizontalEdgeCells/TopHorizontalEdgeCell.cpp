#include "TopHorizontalEdgeCell.h"

TopHorizontalEdgeCell::TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseHorizontalEdgeCell(edgeChar, markedLetter)
{
}

TopHorizontalEdgeCell::TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseHorizontalEdgeCell(edgeChar, markedLetter, cellColor)
{
}

void TopHorizontalEdgeCell::DrawCell(int line) const
{
    if (line == _NEXT_TO_LAST_LINE)
    {
        DrawEmptyLine(_HALF_WIDTH);
        DrawMarkedLetter();
        DrawEmptyLine(_HALF_WIDTH);
    }
    else if (line == _LAST_LINE)
    {
        DrawEmptyLine(_HALF_WIDTH);
        DrawEdge();
        DrawEmptyLine(_HALF_WIDTH);
    }
    else
        DrawEmptyLine(WIDTH);
}