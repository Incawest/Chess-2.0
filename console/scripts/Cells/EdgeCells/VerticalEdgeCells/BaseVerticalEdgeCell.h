#include "BaseEdgeCell.h"

class BaseVerticalEdgeCell : public BaseEdgeCell
{
protected:
    const int _LAST_COL;
    const int _NEXT_TO_LAST_COL;
    const int _MID_HEIGHT;
    const wchar_t _MARKED_DIGIT;

public:
    BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit);
    BaseVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor);
protected:
    virtual void DrawMarkedDigitAndEdge() const = 0;
};