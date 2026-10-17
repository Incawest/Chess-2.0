#include "TopLeftCornerEdgeCell.h"

void TopLeftCornerEdgeCell::DrawCell(int line) const
{
    if (line == _LAST_LINE)
    {
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
        DrawEdge();
    }
    else
        DrawLineBeyondChessboard(_DRAW_FULL_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}