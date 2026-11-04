#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <conio.h>

#include "IUpdatable.h"
#include "Console.h"

enum class MenuAction
{
    MainMenu,
    StartGame,
    Exit
};

class InfoWindowBase : public IUpdatable
{
protected:
    int _totalWidth = 10;
    int _totalHeight = 20;

    int _shiftAlongX = 1;
    int _shiftAlongY = 1;

    int _countWindowRows = 6;
    std::vector<int> _boundaryIndices;
    std::vector<std::wstring> _items;

    bool _isActive;

public:
    InfoWindowBase(bool isActive = true);
    virtual ~InfoWindowBase();

    int GetRequiredWidth() const;
    int GetRequiredHeight() const;

    virtual void PrintContent() const = 0;
    virtual std::optional<MenuAction> HandleMenuSelect();

    void PrintFrame() const;
    void SetShift(int shiftAlongX, int shiftAlongY);

    void NowActive(); //?

private:
    struct FrameParts final
    {
        static inline constexpr wchar_t HORIZONTAL_BORDER = L'\u2501';
        static inline constexpr wchar_t VERTICAL_BORDER = L'\u2503';
        static inline constexpr wchar_t BOUNDARY_LEFT = L'\u2523';
        static inline constexpr wchar_t BOUNDARY_RIGHT = L'\u252B';
        static inline constexpr wchar_t BOUNDARY_TOP = L'\u2533';
        static inline constexpr wchar_t BOUNDARY_BOTTOM = L'\u253B';
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u250F';
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u2513';
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2517';
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u251B';
    
        virtual ~FrameParts() = 0;
    };

};