#pragma once
#include "BaseChessPiece.h"
#include "IDescribable.h"

class Pawn final : public BaseChessPiece, public IDescribable
{
public:
    Pawn();
    explicit Pawn(bool isWhitePiece);
    Pawn(const Pawn& other);
    Pawn(Pawn&& other) noexcept;
    Pawn& operator=(const Pawn& other) = default;
    Pawn& operator=(Pawn&& other) noexcept = default;
    ~Pawn() noexcept override;
    std::string GetClassName() const;
    std::string Describe() const override;
    std::unique_ptr<BaseChessPiece> Clone() const override;
};
