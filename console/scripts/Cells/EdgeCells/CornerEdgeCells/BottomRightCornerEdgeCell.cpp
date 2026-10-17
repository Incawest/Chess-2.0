#include "BottomRightCornerEdgeCell.h"

void BottomRightCornerEdgeCell::DrawCell(int line) const
{
    if (line == 0)
    {
        DrawEdge();
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
    }
    else
        DrawLineBeyondChessboard(_DRAW_FULL_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}