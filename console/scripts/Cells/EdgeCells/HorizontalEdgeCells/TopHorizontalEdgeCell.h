#include "BaseHorizontalEdgeCell.h"

class TopHorizontalEdgeCell : public BaseHorizontalEdgeCell
{
private:
    const int _LAST_LINE;
    const int _NEXT_TO_LAST_LINE;

public:
    TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter);
    TopHorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor);
    virtual void DrawCell(int line) const override;
};