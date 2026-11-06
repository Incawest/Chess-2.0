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
        RGB(int r, int g, int b);
        RGB(const RGB& other);
        RGB(RGB&& other) noexcept;
        RGB& operator=(const RGB& other);
        RGB& operator=(RGB&& other) noexcept;
    };
    
    struct Color final
    {
        static inline const RGB BLACK = RGB{0, 0, 0};
        static inline const RGB BLUE = RGB{0, 0, 255};
        static inline const RGB CYAN = RGB{0, 255, 255};
        static inline const RGB GRAY = RGB{128, 128, 128};
        static inline const RGB GREEN = RGB{0, 255, 0};
        static inline const RGB LIGHT_BLUE = RGB{173, 216, 230};
        static inline const RGB LIGHT_CYAN = RGB{224, 255, 255};
        static inline const RGB LIGHT_GREEN = RGB{144, 238, 144};
        static inline const RGB LIGHT_MAGENTA = RGB{255, 182, 255};
        static inline const RGB LIGHT_RED = RGB{255, 182, 193};
        static inline const RGB LIGHT_YELLOW = RGB{255, 255, 182};
        static inline const RGB MAGENTA = RGB{255, 0, 255};
        static inline const RGB RED = RGB{255, 0, 0};
        static inline const RGB WHITE = RGB{255, 255, 255};
        static inline const RGB YELLOW = RGB{255, 255, 0};

        virtual ~Color() = 0;
    };

private:
    static inline const RGB* _textColor = nullptr;
    static inline const RGB* _bgColor = nullptr;
    static inline const HANDLE _OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    virtual ~Console() = 0;

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

