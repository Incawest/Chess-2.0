#include "LeftVerticalEdgeCell.h"

LeftVerticalEdgeCell::LeftVerticalEdgeCell(wchar_t edgeChar, int markedDigit) :
    LeftVerticalEdgeCell{edgeChar, markedDigit, nullptr}
{
}

LeftVerticalEdgeCell::LeftVerticalEdgeCell(wchar_t edgeChar, int markedDigit, const RGB* cellColor) :
    BaseVerticalEdgeCell{[this](){
        auto pastTextColor = Console::GetTextColor();
        Console::SetTextColor(_cellColor);
        std::wcout << _MARKED_DIGIT;
        Console::SetTextColor(pastTextColor);
        DrawEmptyLine(_NEXT_TO_LAST_COL);
    },edgeChar, markedDigit, cellColor}
{
}

void LeftVerticalEdgeCell::DrawCell(int line) const
{
    if (line == _MID_HEIGHT)
        DrawLineBeyondChessboard(_DRAW_LINE_BEYOND_CHESSBOARD_FUNC);
    else
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
    DrawEdge(_DRAW_EDGE_CHARS_FUNC);
}