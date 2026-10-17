#include "BottomHorizontalEdgeCell.h"

void BottomHorizontalEdgeCell::DrawCell(int line) const
{
    if (line == 0)
        DrawEdge();
    else if (line == 1)
        DrawLineBeyondChessboard(_DRAW_LINE_BEYOND_CHESSBOARD_FUNC);
    else
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
}