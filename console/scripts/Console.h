#pragma once

#include <iostream>
#include <windows.h>

#undef RGB

class Console
{
public:
    struct Color;

    struct RGB final
    {
        int r;
        int g;
        int b;

    private:
        friend struct Color;
        constexpr RGB(int r, int g, int b) noexcept : r{r}, g{g}, b{b}
        {
        }
        RGB(const RGB& other) noexcept = default;
        RGB(RGB&& other) noexcept = default;
        RGB& operator=(const RGB& other) noexcept = default;
        RGB& operator=(RGB&& other) noexcept = default;
    };

private:
    static inline const RGB* _textColor = nullptr;
    static inline const RGB* _bgColor = nullptr;
    static inline const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    Console() = delete;
    static const RGB* GetTextColor();
    static const RGB* GetBGColor();
    static void SetTextColor(const RGB* Color);
    static void SetBGColor(const RGB* Color);
    static void ResetTextColor();
    static void ResetBGColor();
    static void ResetConsoleColor();

    static void ResetCaret();
    static void RefreshConsole();
    static bool IsThisFitInConsole(int rowCnt, int colCnt);
};

struct Console::Color final
{
    static constexpr RGB BLACK{0, 0, 0};
    static constexpr RGB BLUE{0, 0, 255};
    static constexpr RGB CYAN{0, 255, 255};
    static constexpr RGB GRAY{128, 128, 128};
    static constexpr RGB GREEN{0, 255, 0};
    static constexpr RGB LIGHT_BLUE{173, 216, 230};
    static constexpr RGB LIGHT_CYAN {224, 255, 255};
    static constexpr RGB LIGHT_GREEN{144, 238, 144};
    static constexpr RGB LIGHT_MAGENTA{255, 182, 255};
    static constexpr RGB LIGHT_RED{255, 182, 193};
    static constexpr RGB LIGHT_YELLOW{255, 255, 182};
    static constexpr RGB MAGENTA{255, 0, 255};
    static constexpr RGB RED{255, 0, 0};
    static constexpr RGB WHITE{255, 255, 255};
    static constexpr RGB YELLOW{255, 255, 0};

    Color() = delete;
};