#include "RightVerticalEdgeCell.h"

RightVerticalEdgeCell::RightVerticalEdgeCell(wchar_t edgeChar, int markedDigit) :
    RightVerticalEdgeCell{edgeChar, markedDigit, nullptr}
{
}

RightVerticalEdgeCell::RightVerticalEdgeCell(wchar_t edgeChar, int markedDigit, const RGB* cellColor) :
    BaseVerticalEdgeCell{[this](){
        DrawEmptyLine(_NEXT_TO_LAST_COL);
        auto pastTextColor = Console::GetTextColor();
        Console::SetTextColor(_cellColor);
        std::wcout << _MARKED_DIGIT;
        Console::SetTextColor(pastTextColor);
    }, edgeChar, markedDigit, cellColor}
{
}


void RightVerticalEdgeCell::DrawCell(int line) const
{
    DrawEdge(_DRAW_EDGE_CHARS_FUNC);
    if (line == _MID_HEIGHT)
        DrawLineBeyondChessboard(_DRAW_LINE_BEYOND_CHESSBOARD_FUNC);
    else
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}