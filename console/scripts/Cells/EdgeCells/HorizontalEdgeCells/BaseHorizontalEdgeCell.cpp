#include "BaseHorizontalEdgeCell.h"

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter) :
    BaseHorizontalEdgeCell{edgeChar, markedLetter, nullptr}
{
}

BaseHorizontalEdgeCell::BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor) :
    BaseEdgeCell{[this](){
        for (std::size_t i = 0; i < WIDTH; ++i)
            std::wcout << _EDGE_CHAR;
    }, edgeChar, cellColor}, _MARKED_LETTER{markedLetter}
{
}

void BaseHorizontalEdgeCell::DrawMarkedLetter() const
{
    auto pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_cellColor);
    std::wcout << _MARKED_LETTER;
    Console::SetTextColor(pastTextColor);
}