#pragma once

#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "AllEdgeCells.h"
#include "BaseBoardCell.h"
#include "CellsConfiguration.h"
#include "ChessPiece.h"
#include "Console.h"
#include "IUpdatable.h"
#include "Utilits.h"
#include "Vector2.h"

class BaseChessboard : public IUpdatable
{
private:
    struct ChessboardParts final
    {
        static inline constexpr wchar_t TOP_BORDER = L'\u2580';  
        static inline constexpr wchar_t BOTTOM_BORDER = L'\u2584';  
        static inline constexpr wchar_t RIGHT_BORDER = L'\u2590';  
        static inline constexpr wchar_t LEFT_BORDER = L'\u258C';  
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u259B';  
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u259C';  
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2599';  
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u259F';

        ChessboardParts() = delete;
    };

    struct ChessboardEdges final
    {
        std::array<CornerEdgeCell, 4> corners;
        std::vector<HorizontalEdgeCell> topHorizontalEdge;
        std::vector<HorizontalEdgeCell> bottomHorizontalEdge;
        std::vector<VerticalEdgeCell> leftVerticalEdge;
        std::vector<VerticalEdgeCell> rightVerticalEdge;
        std::vector<EdgeConnector> topEdgeConnectors;
        std::vector<EdgeConnector> bottomEdgeConnectors;
    };

public:
    const std::size_t CHESSBOARD_SIZE;

protected:
    using Corners = std::array<CornerEdgeCell, 4>;

private:
    const std::size_t CHESSBOARD_SQUARE;
	std::vector<BaseBoardCell> _cells;
    ChessboardEdges _edges;

    int _selectedCellIndex = -1;
    int _selectedMarkedCellIndex = -1;

    std::vector<Vector2> _positionsOfMarkedCells{};

public:
	explicit BaseChessboard(std::size_t chessboardSize);
    BaseChessboard(std::size_t chessboardSize, Corners corners);
    virtual ~BaseChessboard() = default;

    std::size_t GetChessboardSize() const noexcept;
    void SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, Vector2 position) noexcept;
    void SetSelectedCell(Vector2 position);
    void SetNextMarkedCell(Utilits::DeltaMove direction);

    [[nodiscard]] bool CalculateAllowedMoves();
    void ClearAllowedMoves();

	void Update() override;

private:
	void BuildChessboard();

    void SetCellSelection(std::size_t cellIndex, bool isSelected);
    void SetEdgesSelection(Vector2 intersection, bool isSelected);
    void SetEdgesSelection(std::size_t intersectionIndex, bool isSelected);
    void SetMarkAlongEntireVectorOfMarkedCells(bool isMarked);

    inline Vector2 CalculateCellPosition(std::size_t index) const noexcept;
    inline std::size_t CalculateCellIndex(Vector2 cellPosition) const noexcept; 

    void SortPositionsOfMarkedCells();

    void DrawEdge(const CornerEdgeCell* leftCorner, 
        const std::vector<HorizontalEdgeCell>& edge, 
        const CornerEdgeCell* rightCorner,
        const std::vector<EdgeConnector>& connectors) const;
        
	void DrawChessboard() const;
};