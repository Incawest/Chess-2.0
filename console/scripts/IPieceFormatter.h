#pragma once
#include <string>
#include "BaseChessPiece.h"

class IPieceFormatter
{
public:
    virtual ~IPieceFormatter() noexcept = default;
    virtual std::string Format(const BaseChessPiece& piece) const = 0;
};
