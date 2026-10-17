#include "BaseHorizontalEdgeCell.h"

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseHorizontalEdgeCell(edgeChar, markedLetter, nullptr)
{
}

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseEdgeCell(edgeChar, cellColor), _MARKED_LETTER{markedLetter}
{
}

void BaseHorizontalEdgeCell::DrawEdge() const
{
    auto pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_cellColor);
    std::wcout << std::wstring(WIDTH, _EDGE_CHAR);
    Console::SetTextColor(pastTextColor);
}

void BaseHorizontalEdgeCell::DrawMarkedLetter() const
{
    auto pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_cellColor);
    std::wcout << _MARKED_LETTER;
    Console::SetTextColor(pastTextColor);
}