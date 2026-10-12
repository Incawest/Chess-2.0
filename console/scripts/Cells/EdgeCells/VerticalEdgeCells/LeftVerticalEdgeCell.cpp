#include "LeftVerticalEdgeCell.h"

LeftVerticalEdgeCell::LeftVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit) :
    BaseVerticalEdgeCell(markedDigit, edgeChar)
{
}

LeftVerticalEdgeCell::LeftVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor) :
    BaseVerticalEdgeCell(markedDigit, edgeChar, cellColor)
{
}

void LeftVerticalEdgeCell::DrawCell(int line) const
{
    if (line == _MID_HEIGHT)
    {
        DrawEmptyLine(_NEXT_TO_LAST_COL);
        DrawMarkedDigitAndEdge();
    }
    else
    {
        DrawEmptyLine(_LAST_COL);
        DrawEdge();
    }
}

void LeftVerticalEdgeCell::DrawMarkedDigitAndEdge() const
{
    auto pastTextColor = SetConsoleTextColorAsCellColor();
    std::wcout << _MARKED_DIGIT << _EDGE_CHAR;
    SetConsoleTextColorAsAnotherColor(pastTextColor);
}