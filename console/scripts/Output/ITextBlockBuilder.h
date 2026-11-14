#pragma once

#include "TextBlock.h"

class ITextBlockBuilder
{
public:
    virtual ~ITextBlockBuilder() noexcept = default;
    TextBlock virtual BuildTextBlock(const TextBlock::RGB* textColor, const TextBlock::RGB* bgColor) const = 0;
};