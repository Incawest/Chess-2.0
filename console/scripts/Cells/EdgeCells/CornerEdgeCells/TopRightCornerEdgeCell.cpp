#include "TopRightCornerEdgeCell.h"

void TopRightCornerEdgeCell::DrawCell(int line) const
{
    if (line == _LAST_LINE)
    {
        DrawEdge();
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
    }
    else
        DrawLineBeyondChessboard(_DRAW_FULL_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}