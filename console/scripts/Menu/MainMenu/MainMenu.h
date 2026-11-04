#pragma once

#include "InfoWindowBase.h"

class MainMenu : public InfoWindowBase
{
private:
    std::wstring _title;

    int _selectedIndex = 0;

public:
    MainMenu();

    void Update() override;

    int GetMaxWidth() const;

    void PrintContent() const override;
    std::optional<MenuAction> HandleMenuSelect() override;
    std::optional<MenuAction> SelectItem() const;
};