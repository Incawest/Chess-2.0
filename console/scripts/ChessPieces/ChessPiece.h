#pragma once

#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

#include "Blinkable.h"
#include "Console.h"
#include "TextBlock.h"
#include "Vector2.h"

class ChessPiece : public Blinkable
{
public:
    struct MovePosition
    {
    private:
        friend ChessPiece;
        Vector2 _position{0, 0};
        bool _isMoveForCapturingPieceOnly = false;
    public:
        MovePosition() noexcept;
        MovePosition(Vector2 position, bool isMoveForCapturingPieceOnly) noexcept;
        Vector2 GetPosition() const noexcept;
        bool GetIsMoveForCapturingPieceOnly() const noexcept;
    };
    class Key
    {
        friend ChessPiece;
    private:
        Key() noexcept = default;
    };

private:
    using RGB = TextBlock::RGB;
    using Color = TextBlock::Color;
    using Line = TextBlock::Line;

protected:
    wchar_t _character;
    bool _isWhite;
    bool _isCapturable = false;
    const RGB* _pieceColor;
    Vector2 _position{0, 0};
    std::vector<std::vector<MovePosition>> _pathsForMoves;

private:
    static constexpr const RGB* CAPTURABLE_PIECE_COLOR = &Color::RED;
    const RGB* _defaultPieceColor;
    bool _isAlive = true;

public:
    ChessPiece(const Key& constructorKey, wchar_t type, bool isWhite, std::size_t pathsForMovesCount);

    virtual ~ChessPiece() = default;
    
    template <std::derived_from<ChessPiece> Piece>
    static std::unique_ptr<Piece> InitializeUniqueChessPiece(bool isWhite)
    {
        std::unique_ptr<Piece> newPiece = std::make_unique<Piece>(Key{}, isWhite);
        ChessPiece& base = *newPiece;
        base.InitializePathsForMoves();
        return newPiece;
    }

    template <std::derived_from<ChessPiece> Piece>
    static std::shared_ptr<Piece> InitializeSharedChessPiece(bool isWhite)
    {
        std::shared_ptr<Piece> newPiece = std::make_shared<Piece>(Key{}, isWhite);
        ChessPiece& base = *newPiece;
        base.InitializePathsForMoves();
        return newPiece;
    }

    bool GetIsWhite() const noexcept;
    const RGB* GetColor() const noexcept;
    Vector2 GetPosition() const noexcept;
    std::size_t GetCountOfFullPaths() const noexcept;
    std::span<const MovePosition> GetFullPathForMove(int pathForMoveIndex) const;
    void SetIsCapturable(bool isCapturable);
    void SetPosition(Vector2 position) noexcept;
    void AddPiece(Line& line) const;

    void Update() override;
protected:
    virtual void InitializePathsForMoves() = 0;
};