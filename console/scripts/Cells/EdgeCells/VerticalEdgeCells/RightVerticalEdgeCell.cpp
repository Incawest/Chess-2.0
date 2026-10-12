#include "RightVerticalEdgeCell.h"

RightVerticalEdgeCell::RightVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit) :
    BaseVerticalEdgeCell(markedDigit, edgeChar)
{
}

RightVerticalEdgeCell::RightVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor) :
    BaseVerticalEdgeCell(markedDigit, edgeChar, cellColor)
{
}

void RightVerticalEdgeCell::DrawCell(int line) const
{
    if (line == _MID_HEIGHT)
    {
        DrawMarkedDigitAndEdge();
        DrawEmptyLine(_NEXT_TO_LAST_COL);
    }
    else
    {
        DrawEdge();
        DrawEmptyLine(_LAST_COL);
    }
}

void RightVerticalEdgeCell::DrawMarkedDigitAndEdge() const
{
    auto pastTextColor = SetConsoleTextColorAsCellColor();
    std::wcout << _EDGE_CHAR << _MARKED_DIGIT;
    SetConsoleTextColorAsAnotherColor(pastTextColor);
}