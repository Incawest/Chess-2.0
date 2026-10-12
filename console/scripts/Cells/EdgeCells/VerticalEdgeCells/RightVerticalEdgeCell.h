#include "BaseVerticalEdgeCell.h"

class RightVerticalEdgeCell : public BaseVerticalEdgeCell
{
public:
    RightVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit);
    RightVerticalEdgeCell(wchar_t edgeChar, wchar_t markedDigit, const RGB* cellColor);
    virtual void DrawCell(int line) const override;
protected:
    virtual void DrawMarkedDigitAndEdge() const override;
};