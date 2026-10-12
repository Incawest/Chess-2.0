#include "BaseCornerEdgeCell.h"

class BottomLeftCornerEdgeCell : public BaseCornerEdgeCell
{
public:
    BottomLeftCornerEdgeCell(wchar_t edgeChar);
    BottomLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};