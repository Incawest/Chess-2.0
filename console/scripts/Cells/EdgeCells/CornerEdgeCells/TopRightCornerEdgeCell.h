#include "BaseCornerEdgeCell.h"

class TopRightCornerEdgeCell : public BaseCornerEdgeCell
{
private:
    const int _LAST_LINE;
public:
    TopRightCornerEdgeCell(wchar_t edgeChar);
    TopRightCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
    void DrawCell(int line) const override;
};