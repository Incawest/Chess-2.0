#include "BaseEdgeCell.h"

BaseEdgeCell::BaseEdgeCell(int width, int height, wchar_t edgeChar) : 
    WIDTH{width}, HEIGHT{height}, _EDGE_CHAR{edgeChar}
{
}

BaseEdgeCell::BaseEdgeCell(int width, int height, wchar_t edgeChar, const RGB* cellColor) : 
    WIDTH{width}, HEIGHT{height}, _EDGE_CHAR{edgeChar}, _cellColor{cellColor}
{
}

void BaseEdgeCell::SetCellColor(const RGB* cellColor)
{
    _cellColor = cellColor;
}

const RGB* BaseEdgeCell::SetConsoleTextColorAsCellColor() const
{
    if (_cellColor != nullptr)
    {
        const RGB* pastTextColor = Console::GetTextColor();
        Console::SetTextColor(_cellColor);
        return pastTextColor;
    }
    else
        return nullptr;
}

void BaseEdgeCell::SetConsoleTextColorAsAnotherColor(const RGB* anotherColor) const
{
    if (anotherColor != nullptr)
        Console::SetTextColor(_cellColor);
}

void BaseEdgeCell::DrawEdge() const
{
    auto pastTextColor = SetConsoleTextColorAsCellColor();
    std::wcout << _EDGE_CHAR;
    SetConsoleTextColorAsAnotherColor(pastTextColor);
}

void BaseEdgeCell::DrawEmptyLine(int length) const
{
    if (length == 0)
        return;
    std::wcout << std::wstring(length, L' ');
}
