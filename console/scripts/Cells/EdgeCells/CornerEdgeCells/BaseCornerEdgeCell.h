#include "BaseEdgeCell.h"

class BaseCornerEdgeCell : public BaseEdgeCell
{
protected:
    const int _LAST_COL;
public:
    BaseCornerEdgeCell(wchar_t edgeChar);
    BaseCornerEdgeCell(wchar_t edgeChar, const RGB* cellColor);
};