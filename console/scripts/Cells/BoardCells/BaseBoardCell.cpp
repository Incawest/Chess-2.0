#include "BaseBoardCell.h"

BaseBoardCell::CellboardParts::~CellboardParts() = default;

BaseBoardCell::BaseBoardCell() = default;

BaseBoardCell::BaseBoardCell(const RGB* cellColor) : _cellColor{cellColor}
{
}

BaseBoardCell::BaseBoardCell(const RGB* cellColor, std::weak_ptr<ChessPiece> piece) : BaseBoardCell(cellColor) 
{
    SetPieceOnCell(piece);
}

const RGB* BaseBoardCell::GetPieceColor() const
{
    auto piece = _piece.lock();
    if ( piece != nullptr)
    {
        return piece->GetColor();
    }
    else
    {
        return nullptr;
    }
}

const RGB* BaseBoardCell::GetCellColor() const
{
    return _cellColor;
}

void BaseBoardCell::SetPieceOnCell(
    std::weak_ptr<ChessPiece> piece
) 
{
    _piece = piece;
}

void BaseBoardCell::DrawCell(int line) const
{
    const RGB* pastTextColor = Console::GetTextColor();
    Console::SetTextColor(_cellColor);

    if (line == 0)
    {
        std::wcout << CellboardParts::TOP_LEFT_CORNER;
        std::wcout << std::wstring{_HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER};
        std::wcout << CellboardParts::TOP_RIGHT_CORNER;
    }
    
    else if (line == _LAST_LINE)
    {
        std::wcout << CellboardParts::BOTTOM_LEFT_CORNER;
        std::wcout << std::wstring{_HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER};
        std::wcout << CellboardParts::BOTTOM_RIGHT_CORNER;
    }
    else
    {
        std::wcout << CellboardParts::VERTICAL_BORDER;
        
        auto piece = _piece.lock();
        if (piece != nullptr) 
        {
            if (_cellColor != nullptr)
                piece->DrawPiece();
        }
        else
            DrawEmptyLine(_HORIZONTAL_WIDTH);

        std::wcout << CellboardParts::VERTICAL_BORDER;
    }

    Console::SetTextColor(pastTextColor);
}