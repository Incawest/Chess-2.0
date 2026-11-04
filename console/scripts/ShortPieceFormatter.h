#pragma once
#include "IPieceFormatter.h"

class ShortPieceFormatter final : public IPieceFormatter
{
public:
    std::string Format(const BaseChessPiece& piece) const override;
};
