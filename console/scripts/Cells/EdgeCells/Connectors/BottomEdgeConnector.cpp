#include "BottomEdgeConnector.h"

void BottomEdgeConnector::DrawCell(int line) const
{
    if (line == 0)
        DrawEdge();
    else
        DrawLineBeyondChessboard(_DRAW_EMPTY_LINE_BEYOND_CHESSBOARD);
}