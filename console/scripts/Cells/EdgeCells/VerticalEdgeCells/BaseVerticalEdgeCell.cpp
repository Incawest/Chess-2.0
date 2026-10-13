#include "BaseVerticalEdgeCell.h"

BaseVerticalEdgeCell::BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit) :
    BaseEdgeCell(edgeChar), _MARKED_DIGIT{markedDigit}
{
}

BaseVerticalEdgeCell::BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor) :
    BaseEdgeCell(edgeChar, cellColor), _MARKED_DIGIT{markedDigit}
{
}