#pragma once

#include <iostream>
#include <vector>

#include "Console.h"

using Color = Console::Color;
using RGB = Console::RGB;

class BaseEdgeCell
{
public:
    const int WIDTH;  
    const int HEIGHT;

protected:
    const wchar_t _EDGE_CHAR;
    const RGB* _cellColor = nullptr;

public:
    BaseEdgeCell(int width, int height, wchar_t edgeChar);
    BaseEdgeCell(int width, int height, wchar_t edgeChar, const RGB* cellColor);
    void SetCellColor(const RGB* cellColor);

    virtual void DrawCell(int line) const = 0;
protected:
    const RGB* SetConsoleTextColorAsCellColor() const;
    void SetConsoleTextColorAsAnotherColor(const RGB* anotherColor) const;
    void DrawEdge() const;
    void DrawEmptyLine(int length) const;
};