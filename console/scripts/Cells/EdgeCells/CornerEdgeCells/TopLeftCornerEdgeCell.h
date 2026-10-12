#include "BaseCornerEdgeCell.h"

class TopLeftCornerEdgeCell : public BaseCornerEdgeCell
{
private:
    const int _LAST_LINE;
public:
    TopLeftCornerEdgeCell(wchar_t edgeChar);
    TopLeftCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};