#include "TopHorizontalEdgeCell.h"

void TopHorizontalEdgeCell::DrawCell(int line) const
{
    if (line == _NEXT_TO_LAST_LINE)
        DrawLineBeyondChessboard(_DRAW_LINE_BEYOND_CHESSBOARD_FUNC);
    else if (line == _LAST_LINE)
        DrawEdge(_DRAW_EDGE_CHARS_FUNC);
    else
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}