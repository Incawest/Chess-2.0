#include "BaseHorizontalEdgeCell.h"

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseEdgeCell(5, 2, edgeChar), _HALF_WIDTH{WIDTH / 2}, _MARKED_LETTER{markedLetter}
{
}

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseEdgeCell(5, 2, edgeChar), _HALF_WIDTH{WIDTH / 2}, _MARKED_LETTER{markedLetter}
{
}

void BaseHorizontalEdgeCell::DrawMarkedLetter() const
{
    auto pastTextColor = SetConsoleTextColorAsCellColor();
    std::wcout << _MARKED_LETTER;
    SetConsoleTextColorAsAnotherColor(pastTextColor);
}