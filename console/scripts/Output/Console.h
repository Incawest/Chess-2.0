#pragma once

#include <algorithm>
#include <iostream>
#include <span>
#include <stdexcept>
#include <system_error>
#include <windows.h>
#undef RGB

#include "Vector2.h"
#include "TextBlock.h"

class Console
{
private:
    static inline const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
    static constexpr std::size_t MAX_WRITABLE_CHUNK_CHARS = 32 * 1024;
public:
    Console() = delete;

    static bool DoesThisFitInConsole(Vector2 size)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(OUTPUT_HANDLE, &info))
            return false;

        std::size_t consoleRowCnt = info.srWindow.Bottom - info.srWindow.Top + 1;
        std::size_t consoleColCnt = info.srWindow.Right - info.srWindow.Left + 1;

        return size.row <= consoleRowCnt && size.col <= consoleColCnt;
    }

    static void ResetCaret()
    {
        std::wcout << L"\033[1;1H" << std::flush;
    }

    static void RefreshConsoleAfterCaret()
    {
        std::wcout << L"\033[J" << std::flush;
    }

    static void RefreshConsole()
    {
        std::wcout << L"\033[2J\033[3J";
        ResetCaret();
    }

    static void DrawTextBlocks(std::span<const TextBlock> squaredFilledTextBlocks)
    {
        std::wstring result;

        result += GetInOneLine(squaredFilledTextBlocks);
        DrawWstring(result);
    }

    static void DrawWstring(std::wstring_view wst)
    {
        while (!wst.empty())
        {
            const DWORD charsCount = static_cast<DWORD>(std::min(wst.size(), MAX_WRITABLE_CHUNK_CHARS));
            DWORD writtenChars = 0;

            if (!WriteConsoleW(OUTPUT_HANDLE, wst.data(), charsCount, &writtenChars, nullptr))
                throw std::system_error(static_cast<int>(GetLastError()), std::system_category(), "WriteConsoleW");
            else if (writtenChars == 0)
                throw std::runtime_error("WriteConsoleW has written no characters");

            wst.remove_prefix(writtenChars);
        }
    }

private:
    static std::wstring GetInOneLine( std::span<const TextBlock> squaredFilledTextBlocks)
    {
        static TextBlock::Line resetLine = [](){
            TextBlock::Line rl;
            rl.ResetTextColor();
            rl.ResetBGColor();
            return rl;
        }();
        static std::wstring_view resetColors = resetLine;

        std::size_t height = 0;
        std::size_t commonWidth = 0;
        std::size_t visibleTextBlocks = 0;
        for (const TextBlock& textBlock : squaredFilledTextBlocks)
        {
            std::size_t linesCount = textBlock.GetLinesCount();

            if (linesCount == 0)
                continue;

            height = std::max(height, linesCount);
            commonWidth += textBlock.gapBefore + textBlock[0].GetWidth();
            ++visibleTextBlocks;
        }

        ++commonWidth;

        std::size_t textBlocksCount = squaredFilledTextBlocks.size();

        std::wstring result;
        result.reserve(height * commonWidth + (visibleTextBlocks * height + 1) * resetColors.size());

        result.append(resetColors);
        for (std::size_t y = 0; y < height; ++y)
        {
            if (y > 0)
                result += L'\n';
            for (std::size_t i = 0; i < textBlocksCount; ++i)
            {
                const TextBlock& textBlock = squaredFilledTextBlocks[i];    
                std::size_t linesCount = textBlock.GetLinesCount();
                if (linesCount == 0)
                    continue;

                result.append(textBlock.gapBefore, L' ');

                if (y < linesCount)
                {
                    result += static_cast<std::wstring_view>(textBlock[y]);
                    result.append(resetColors);
                }
                else
                    result.append(textBlock[0].GetWidth(), L' ');
            }
        }

        return result;
    }
};