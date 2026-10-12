#include "BaseCornerEdgeCell.h"

class BottomRightCornerEdgeCell : public BaseCornerEdgeCell
{
public:
    BottomRightCornerEdgeCell(wchar_t edgeChar);
    BottomRightCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};