#include "TextBlock.h"

bool TextBlock::Line::TrySetActiveColor(ColorTarget target, const RGB* activeColor)
{
    return GetColorHandler(target).TrySetActiveColor(*this, activeColor);
}

void TextBlock::Line::SetActiveColorToDefault(ColorTarget target)
{
    GetColorHandler(target).SetActiveColorToDefault(*this);
}

void TextBlock::Line::ResetActiveColor(ColorTarget target)
{
    GetColorHandler(target).ResetActiveColor(*this);
}

void TextBlock::Line::ColorHandler::SetActiveColorToDefault(Line& handlingLine)
{
    if (_defaultColor != nullptr)
        TrySetActiveColor(handlingLine, _defaultColor);
    else
        ResetActiveColor(handlingLine);
}

bool  TextBlock::Line::ColorHandler::TrySetActiveColor(Line& handlingLine, const RGB* activeColor)
{
    if (activeColor != nullptr && activeColor != _activeColor)
    {
        _activeColor = activeColor;

        std::wostringstream wstrStream{std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_app};
        wstrStream
            << L"\x1b" << _setColorCommand
            << _activeColor->r << L';'
            << _activeColor->g << L';'
            << _activeColor->b << L'm';
        handlingLine += wstrStream.str();
        return true;
    }
    else
        return false;
}

void  TextBlock::Line::ColorHandler::ResetActiveColor(Line& handlingLine)
{
    handlingLine += L"\033" + _resetColorCommand;
    _activeColor = nullptr;
}