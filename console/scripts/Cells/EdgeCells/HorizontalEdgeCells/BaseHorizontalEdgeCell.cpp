#include "BaseHorizontalEdgeCell.h"

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseEdgeCell(edgeChar), _MARKED_LETTER{markedLetter}
{
}

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseEdgeCell(edgeChar, cellColor), _MARKED_LETTER{markedLetter}
{
}

void BaseHorizontalEdgeCell::DrawMarkedLetter() const
{
    auto pastTextColor = SetConsoleTextColorAsCellColor();
    std::wcout << _MARKED_LETTER;
    SetConsoleTextColorAsAnotherColor(pastTextColor);
}