#pragma once
#include "IPieceFormatter.h"

class DetailedPieceFormatter final : public IPieceFormatter
{
public:
    std::string Format(const BaseChessPiece& piece) const override;
};
