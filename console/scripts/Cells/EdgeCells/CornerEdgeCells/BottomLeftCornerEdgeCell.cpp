#include "BottomLeftCornerEdgeCell.h"

void BottomLeftCornerEdgeCell::DrawCell(int line) const
{
    if (line == 0)
    {
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
        DrawEdge(_DRAW_EDGE_CHARS_FUNC);
    }
    else
        DrawLineBeyondChessboard(_DRAW_FULL_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}