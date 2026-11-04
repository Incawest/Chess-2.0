#include "MainMenu.h"

MainMenu::MainMenu() : InfoWindowBase()
{
    _items = {
        L"Start game",
        L"Inventory",
        L"Shop",
        L"Controls",
        L"Exit",
    };
    _title = L"Chess 2.0";
    _totalWidth = GetMaxWidth() + 4;
    _totalHeight = _items.size() + 2;
    _boundaryIndices = {1};
}

void MainMenu::Update()
{
    if (_isActive) 
    {
        PrintFrame();
        PrintContent();
    }
}

int MainMenu::GetMaxWidth() const
{
    size_t maxLength = 0;

    for (const std::wstring& item : _items)
    {
        if (item.length() > maxLength)
            maxLength = item.length();
    }

    maxLength = (_title.length() > maxLength) ? _title.length() : maxLength;

    return maxLength;
}

void MainMenu::PrintContent() const
{
    int titleX = _shiftAlongX
        + 1
        + (_totalWidth - _title.length()) / 2;

    Console::MoveCaret(titleX, _shiftAlongY + 1);
    std::wcout << _title;

    for (size_t i = 0; i < _items.size(); ++i)
    {
        if (i == _selectedIndex)
        {
            int itemX = _shiftAlongX + 2;
            int itemY = _shiftAlongY + 3 + i;

            Console::MoveCaret(itemX, itemY);
            std::wcout << L'>' << _items[i];
        }
        else
        {
            int itemX = _shiftAlongX + 2;
            int itemY = _shiftAlongY + 3 + i;

            Console::MoveCaret(itemX, itemY);
            std::wcout << L' ' << _items[i];
        }
    }

    std::wcout << std::flush;
}

std::optional<MenuAction> MainMenu::HandleMenuSelect()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == 0 || key == 224)
        {
            key = _getch();

            if (key == 72)
            {
                if (_selectedIndex > 0)
                    --_selectedIndex;
            }
            if (key == 80)
            {
                if (_selectedIndex < (_items.size()-1))
                    ++_selectedIndex;
            }
        }
        else if (key == 13)
        {
            return SelectItem();
        }
    }
    return std::nullopt;
}

std::optional<MenuAction> MainMenu::SelectItem() const
{
    switch (_selectedIndex)
    {
    case 0:
        return MenuAction::StartGame;

    case 4:
        return MenuAction::Exit;

    default:
        return std::nullopt;
    }
}