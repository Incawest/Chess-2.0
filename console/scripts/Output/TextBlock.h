#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct TextBlock
{
public:
    struct Color;

    struct RGB final
    {
        friend struct Color;
    public:
        int r;
        int g;
        int b;
    private:
        constexpr RGB(int r, int g, int b) noexcept : r{r}, g{g}, b{b}
        {
        }
        RGB(const RGB& other) noexcept = default;
        RGB(RGB&& other) noexcept = default;
        RGB& operator=(const RGB& other) noexcept = default;
        RGB& operator=(RGB&& other) noexcept = default;
    };

    class Line
    {
    private:
        std::wstring _line{};
        std::size_t _width = 0;

        const RGB* _defaultTextColor = nullptr;
        const RGB* _defaultBGColor = nullptr;
        const RGB* _currentTextColor = nullptr;
        const RGB* _currentBGColor = nullptr;

    public:
        Line() noexcept = default;

        constexpr Line(const RGB* defaultTextColor, const RGB* defaultBGColor, bool areColorsAlreadySetted, std::wstring line) :
            _defaultTextColor{defaultTextColor}, 
            _defaultBGColor{defaultBGColor},
            _currentTextColor{areColorsAlreadySetted ? _defaultTextColor : nullptr},
            _currentBGColor{areColorsAlreadySetted ? _defaultBGColor : nullptr},
            _line{std::move(line)}, 
            _width{_line.size()}
        {
        }

        constexpr Line(const RGB* defaultTextColor, const RGB* defaultBGColor, bool areColorsAlreadySetted) : 
            Line{defaultTextColor, defaultBGColor, areColorsAlreadySetted, {}}
        {
        }

        constexpr explicit Line(std::wstring line) noexcept : Line{{}, {}, false, line}
        {
        }

        constexpr Line& operator=(std::wstring_view other)
        {
            _line = other;
            _width = other.size();
            return *this;
        }

        constexpr Line& operator+=(const wchar_t& other)
        {
            _line += other;
            _width += 1;
            return *this;
        }

        constexpr Line& operator+=(std::wstring_view other)
        {
            _line += other;
            _width += other.size();
            return *this;
        }

        constexpr Line& operator+=(const Line& other)
        {
            _line += other._line;
            _width += other._width;
            return *this;
        }

        friend constexpr Line operator+(Line first, const Line& second)
        {   
            first += second;
            return first;
        }

        constexpr operator std::wstring_view() const noexcept
        {
            return std::wstring_view{_line};
        }

        constexpr operator std::wstring_view() noexcept
        {
            return std::wstring_view{_line};
        }

        constexpr void AddChars(std::size_t count, wchar_t character = L' ')
        {
            _line.append(count, character);
            _width += count;
        }

        constexpr std::size_t GetWidth() const noexcept
        {
            return _width;
        }

        constexpr const RGB* GetTextColor() const noexcept
        {
            return _currentTextColor;
        }

        constexpr const RGB* GetBGColor() const noexcept
        {
            return _currentBGColor;
        }


        constexpr void SetDefaultTextColor(const RGB* defaultTextColor) noexcept
        {
            _defaultTextColor = defaultTextColor;
        }

        constexpr void SetDefaultBGColor(const RGB* defaultBGColor) noexcept
        {
            _defaultBGColor = defaultBGColor;
        }

        void SetTextColorToDefault();
        void SetBGColorToDefault();
        
        bool TrySetTextColor(const RGB* textColor);
        bool TrySetBGColor(const RGB* bgColor);

        void ResetTextColor();
        void ResetBGColor();
    };
    
public:
    std::size_t gapBefore = 0;

private:
    std::vector<Line> _lines{};

public:
    TextBlock() noexcept = default;

    TextBlock(
        std::size_t linesCount, 
        const RGB* outsideTextColor, 
        const RGB* outsideBGColor, 
        bool areColorsAlreadySetted, 
        std::size_t gapBefore
    ) : gapBefore{gapBefore}
    {
        _lines.reserve(linesCount);
        for (std::size_t i = 0; i < linesCount; ++i)
        {
            _lines.emplace_back(outsideTextColor, outsideBGColor, areColorsAlreadySetted);
            if (!areColorsAlreadySetted)
            {
                _lines[i].SetTextColorToDefault();
                _lines[i].SetBGColorToDefault();
            }
        }
    }

    TextBlock(std::size_t linesCount, const RGB* outsideTextColor, const RGB* outsideBGColor, bool areColorsAlreadySetted) : 
        TextBlock{linesCount, outsideTextColor, outsideBGColor, areColorsAlreadySetted, 0}
    {
    }

    TextBlock(std::size_t linesCount, std::size_t gapBefore) : TextBlock{linesCount, {}, {}, false, gapBefore}
    {
    }

    explicit TextBlock(std::size_t linesCount) : TextBlock{linesCount, 0}
    {
    }

    constexpr Line& operator[](std::size_t index)
    {
        return _lines[index];
    }

    constexpr const Line& operator[](std::size_t index) const
    {
        return _lines[index];
    }
    constexpr auto begin() const noexcept
    {
        return _lines.begin();
    }

    constexpr auto end() const noexcept
    {
        return _lines.end();
    }

    constexpr auto begin() noexcept
    {
        return _lines.begin();
    }

    constexpr auto end() noexcept
    {
        return _lines.end();
    }

    constexpr std::size_t GetLinesCount() const noexcept
    {
        return _lines.size();
    }

    constexpr void AddCharsForSeveralLines(
        std::size_t startIndex, 
        std::size_t linesCount, 
        std::size_t charsCount = 1, 
        wchar_t character = L' ')
    {
        std::size_t maxLinesCount = _lines.size();
        if (startIndex < maxLinesCount)
        {
            std::size_t endIndex = startIndex + linesCount;
            if (endIndex > maxLinesCount)
                endIndex = maxLinesCount;

            for (std::size_t i = startIndex; i < endIndex; ++i)
                _lines[i].AddChars(charsCount, character);
        }
    }

    constexpr void AddLines(std::size_t count)
    {
        for(std::size_t i = 0; i < count; ++i)
            _lines.emplace_back();
    }

    constexpr void RemoveLines(std::size_t startIndex, std::size_t count = 1)
    {
        std::size_t linesSize = _lines.size();
        if (count > 0 && startIndex < linesSize)
        {
            if (count > 1)
            {
                std::size_t lastIndex = startIndex + count;
                std::vector<Line>::iterator firstIt = _lines.begin(), lastIt;
                lastIt = lastIndex > linesSize ? _lines.end() : firstIt + lastIndex;
                _lines.erase(firstIt, lastIt);
            }
            else
                _lines.erase(_lines.begin());
        }
    }

    constexpr void MergeWithTextBlock(const TextBlock& mergingLines, std::size_t startIndexInMain = 0)
    {
        std::size_t mainLinesCount = _lines.size();
        std::size_t mergingLinesCount = mergingLines._lines.size();
        if (startIndexInMain + mergingLinesCount > mainLinesCount)
        {
            if(startIndexInMain > mainLinesCount)
                startIndexInMain = mainLinesCount;

            for (std::size_t i = mergingLinesCount - (mainLinesCount - startIndexInMain); i > 0; --i)
                _lines.emplace_back();
        }

        for (std::size_t i = 0; i < mergingLinesCount; ++i)
            _lines[startIndexInMain + i] += mergingLines._lines[i];
    }
};

struct TextBlock::Color final
{
public:
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