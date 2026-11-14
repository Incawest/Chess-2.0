#include "TextBlock.h"

bool TextBlock::Line::TrySetTextColor(const RGB* textColor)
{
    if (textColor != nullptr && textColor != _currentTextColor)
    {
        _currentTextColor = textColor;

        std::wostringstream wstrStream{std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_app};
        wstrStream
                << L"\x1b[38;2;"
                << _currentTextColor->r << L';'
                << _currentTextColor->g << L';'
                << _currentTextColor->b << L'm';
        *this += wstrStream.str();
        return true;
    }
    else
        return false;
}

bool TextBlock::Line::TrySetBGColor(const RGB* bgColor)
{
    if (bgColor != nullptr && bgColor != _currentBGColor)
    {
        _currentBGColor = bgColor;

        std::wostringstream wstrStream{std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_app};
        wstrStream
            << L"\x1b[48;2;"
            << _currentBGColor->r << L';'
            << _currentBGColor->g << L';'
            << _currentBGColor->b << L'm';
        *this += wstrStream.str();
        return true;
    }
    else
        return false;
}

void TextBlock::Line::SetTextColorToDefault()
{
    if (_defaultTextColor != nullptr)
        TrySetTextColor(_defaultTextColor);
    else
        ResetTextColor();
}


void TextBlock::Line::SetBGColorToDefault()
{
    if (_defaultBGColor != nullptr)
        TrySetBGColor(_defaultBGColor);
    else
        ResetBGColor();
}


void TextBlock::Line::ResetTextColor()
{
    *this += L"\033[39m";
    _currentTextColor = nullptr;
}

void TextBlock::Line::ResetBGColor()
{
    *this += L"\033[49m";
    _currentBGColor = nullptr;
}