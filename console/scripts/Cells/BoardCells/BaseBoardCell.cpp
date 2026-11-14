#include "BaseBoardCell.h"
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

TextBlock BaseBoardCell::BuildTextBlock(const RGB* textColor, const RGB* bgColor) const
{
    TextBlock textBlock{HEIGHT, WIDTH, textColor, bgColor, true};
    
    for (std::size_t i = 0; i < HEIGHT; ++i)
    {
        auto& curLine = textBlock[i];
        bool isSuccess = curLine.TrySetActiveColor(Line::ColorTarget::TEXT, _cellColor);

        if (i == 0)
        {
            curLine += CellboardParts::TOP_LEFT_CORNER;
            curLine.AddChars(HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER);
            curLine += CellboardParts::TOP_RIGHT_CORNER;
        }
        else if (i == LAST_LINE)
        {
            curLine += CellboardParts::BOTTOM_LEFT_CORNER;
            curLine.AddChars(HORIZONTAL_WIDTH, CellboardParts::HORIZONTAL_BORDER);
            curLine += CellboardParts::BOTTOM_RIGHT_CORNER;
        }
        else
        {
            curLine += CellboardParts::VERTICAL_BORDER;
            curLine += L' ';
            
            auto piece = _piece.lock();
            if (piece != nullptr) 
            {
                piece->AddPiece(curLine);
            }
            else if (_isMarked)
            {
                if (_isSelected)
                {
                    auto curCellColor = curLine.GetActiveColor(Line::ColorTarget::TEXT);
                    bool isSuccessOfMark = curLine.TrySetActiveColor(Line::ColorTarget::TEXT, SELECTED_CELL_COLOR);  
                    curLine += CHARACTER_MARK;

                    if(isSuccessOfMark)
                        curLine.TrySetActiveColor(Line::ColorTarget::TEXT, curCellColor);
                }
                else
                    curLine += CHARACTER_MARK;
            }
            else
                curLine += L' ';

            curLine += L' ';
            curLine += CellboardParts::VERTICAL_BORDER;
        }

        if (isSuccess)
            curLine.SetActiveColorToDefault(Line::ColorTarget::TEXT);
    }
    return textBlock;
}

void BaseBoardCell::Update()
{
    BaseCell::SetSelection(GetIsShining());
}