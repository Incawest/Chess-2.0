#include "BaseBoardCell.h"

BaseBoardCell::CellboardParts::~CellboardParts() = default;

BaseBoardCell::BaseBoardCell() = default;

BaseBoardCell::BaseBoardCell(const RGB* cellColor) : BaseCell{cellColor}
{
}

BaseBoardCell::BaseBoardCell(const RGB* cellColor, std::weak_ptr<ChessPiece> piece) : BaseBoardCell{cellColor} 
{
    SetPieceOnCell(piece);
}

std::shared_ptr<ChessPiece> BaseBoardCell::GetChessPiece() const noexcept
{
    return _piece.lock();
}

void BaseBoardCell::SetSelection(bool isSelected)
{
    if (!(_isMarked && _piece.lock() == nullptr))
    {
        BaseCell::SetSelection(isSelected);
        isSelected ? Blinkable::PushUpdatingBlinkable(this) : Blinkable::EraseUpdatingBlinkable(this);
    }
    else if (_isSelected)
        Blinkable::EraseUpdatingBlinkable(this);
    
    _isSelected = isSelected;
}

void BaseBoardCell::SetMark(bool isMarked)
{
    auto realPiece = _piece.lock();
    if (realPiece != nullptr)
        realPiece->SetIsCapturable(isMarked);
    _isMarked = isMarked;

    SetSelection(_isSelected);
}

void BaseBoardCell::SetPieceOnCell(std::weak_ptr<ChessPiece> piece) noexcept
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
        std::wcout << std::wstring(_HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER);
        std::wcout << CellboardParts::TOP_RIGHT_CORNER;
    }
    
    else if (line == _LAST_LINE)
    {
        std::wcout << CellboardParts::BOTTOM_LEFT_CORNER;
        std::wcout << std::wstring(_HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER);
        std::wcout << CellboardParts::BOTTOM_RIGHT_CORNER;
    }
    else
    {
        std::wcout << CellboardParts::VERTICAL_BORDER << L' ';
        
        auto piece = _piece.lock();
        if (piece != nullptr) 
        {
            piece->DrawPiece();
        }
        else if (_isMarked)
        {
            if (_isSelected)
            {
                const RGB* curCellColor = Console::GetTextColor();
                Console::SetTextColor(_SELECTED_CELL_COLOR);  
                std::wcout << _CHARACTER_MARK;
                Console::SetTextColor(curCellColor);
            }
            else
                std::wcout << _CHARACTER_MARK;
        }
        else
            std::wcout << L' ';

        std::wcout << L' ' << CellboardParts::VERTICAL_BORDER;
    }

    Console::SetTextColor(pastTextColor);
}

void BaseBoardCell::Update()
{
    BaseCell::SetSelection(GetIsShining());
}