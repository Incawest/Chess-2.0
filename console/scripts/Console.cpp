#include "Console.h"

Console::RGB::RGB(int r, int g, int b) : r{r}, g{g}, b{b}
{
}

Console::RGB::RGB(const RGB& other) = default;
Console::RGB::RGB(RGB&& other) = default;

Console::Color::~Color() = default;

Console::~Console() = default;

const Console::RGB* Console::GetTextColor()
{
    return _textColor;
}

const Console::RGB* Console::GetBGColor()
{
    return _bgColor;
}

void Console::SetTextColor(const Console::RGB* color)
{
    if (color != nullptr)
    {
        std::wcout
                << L"\x1b[38;2;"
                << color->r << L';'
                << color->g << L';'
                << color->b << L'm';
        _textColor = color;
    }
}

void Console::SetBGColor(const RGB* color)
{
    if (color != nullptr)
    {
        std::wcout
            << L"\x1b[48;2;"
            << color->r << L';'
            << color->g << L';'
            << color->b << L'm';
        _bgColor = color;
    }
}

void Console::ResetTextColor()
{
    std::wcout << L"\033[39m" << std::flush;
}

void Console::ResetBGColor()
{
    std::wcout << L"\033[49m" << std::flush;
}

void Console::ResetConsoleColor()
{
    std::wcout << L"\x1b[0m" << std::flush;
    _textColor = &Color::WHITE;
    _bgColor = &Color::BLACK;
}

void Console::ResetCaret()
{
	std::wcout << L"\033[3J\033[1;1H" << std::flush;
}

void Console::RefreshConsole()
{
    std::wcout << L"\033[2J";
    ResetCaret();
}

bool Console::IsThisFitInConsole(int rowCnt, int colCnt)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(_OUTPUT_HANDLE, &info))
        return false;
    int consoleRowCnt = info.srWindow.Bottom - info.srWindow.Top + 1;
    int consoleColCnt = info.srWindow.Right - info.srWindow.Left + 1;

    return rowCnt <= consoleRowCnt && colCnt <= consoleColCnt;
}