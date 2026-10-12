#include "BaseVerticalEdgeCell.h"

BaseVerticalEdgeCell::BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit) :
    BaseEdgeCell(2, 3, edgeChar), 
    _MID_HEIGHT{HEIGHT / 2}, _LAST_COL {WIDTH - 1}, _NEXT_TO_LAST_COL {WIDTH - 2}, _MARKED_DIGIT{markedDigit}
{
}

BaseVerticalEdgeCell::BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor) :
    BaseEdgeCell(2, 3, edgeChar), 
    _MID_HEIGHT{HEIGHT / 2}, _LAST_COL {WIDTH - 1}, _NEXT_TO_LAST_COL {WIDTH - 2}, _MARKED_DIGIT{markedDigit}
{
}