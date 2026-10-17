#include "BaseVerticalEdgeCell.h"

BaseVerticalEdgeCell::BaseVerticalEdgeCell(std::function<void()> drawLineBeyondChessboardFunc, wchar_t edgeChar, int markedDigit) :
    BaseVerticalEdgeCell(drawLineBeyondChessboardFunc, edgeChar, markedDigit, nullptr)
{
}

BaseVerticalEdgeCell::BaseVerticalEdgeCell(std::function<void()> drawLineBeyondChessboardFunc, wchar_t edgeChar, int markedDigit, const RGB* cellColor) :
    BaseEdgeCell(edgeChar, cellColor), _DRAW_LINE_BEYOND_CHESSBOARD_FUNC{drawLineBeyondChessboardFunc}, _MARKED_DIGIT{markedDigit}
{
}