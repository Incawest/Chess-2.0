#include "TopEdgeConnector.h"

void TopEdgeConnector::DrawCell(int line) const
{
    if (line == 0)
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD_FUNC);
    else
        DrawEdge(_DRAW_EDGE_CHARS_FUNC);
}