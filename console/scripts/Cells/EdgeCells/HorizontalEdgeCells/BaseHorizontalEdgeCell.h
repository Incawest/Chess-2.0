#include "BaseEdgeCell.h"

class BaseHorizontalEdgeCell : public BaseEdgeCell
{
protected:
    const int _HALF_WIDTH;
    const wchar_t _MARKED_LETTER;

public:
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    BaseHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
protected:
    void DrawMarkedLetter() const;
};