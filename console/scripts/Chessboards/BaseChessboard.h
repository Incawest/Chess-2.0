#pragma once

#include <algorithm>
#include <concepts>
#include <iostream>
#include <iterator>
#include <memory>
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
public:
    enum class DeltaMove
    {
        UP,
        LEFT,
        RIGHT,
        DOWN
    };
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

        virtual ~ChessboardParts() = 0;
    };

    struct ChessboardEdges final
    {
        std::vector<std::unique_ptr<BaseCornerEdgeCell>> corners;
        std::vector<std::unique_ptr<TopHorizontalEdgeCell>> topHorizontalEdge;
        std::vector<std::unique_ptr<BottomHorizontalEdgeCell>> bottomHorizontalEdge;
        std::vector<std::unique_ptr<LeftVerticalEdgeCell>> leftVerticalEdge;
        std::vector<std::unique_ptr<RightVerticalEdgeCell>> rightVerticalEdge;
        std::vector<std::unique_ptr<TopEdgeConnector>> topEdgeConnectors;
        std::vector<std::unique_ptr<BottomEdgeConnector>> bottomEdgeConnectors;
    };

private:
    const std::size_t _CHESSBOARD_SIZE;
    const std::size_t _CHESSBOARD_SQUARE;
	std::vector<std::unique_ptr<BaseBoardCell>> _cells;
    ChessboardEdges _edges;

    int _selectedCellIndex = -1;
    int _selectedMarkedCellIndex = -1;

    std::vector<Vector2> _positionsOfMarkedCells{};

public:
	BaseChessboard(std::size_t chessBoardSize);
    virtual ~BaseChessboard();

    std::size_t GetChessboardSize() const noexcept;
    std::size_t GetAllowedMovesCount() const noexcept;
    void SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, Vector2 position) noexcept;
    void SetSelectedCell(Vector2 position);
    void SetNextMarkedCell(DeltaMove deltaMove);

    void CalculateAllowedMoves();
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

    template <std::ranges::forward_range Range>
    int CalculateNearestCellIndex(Range&& range, Vector2 anchoredPosition) const;

    template <std::predicate<const Vector2&> PrimaryPredicate,  std::predicate<const Vector2&> SecondaryPredicate>
    int CalculateNextMarkedCellIndex(PrimaryPredicate primaryCondition, SecondaryPredicate secondaryCondition, Vector2 anchoredPosition,
        DeltaMove priorityDirection) const; 

    void SortPositionsOfMarkedCells();

    template <std::derived_from<BaseHorizontalEdgeCell> HorizontalEdgeCell, std::derived_from<BaseEdgeConnector> EdgeConnector>
    void DrawEdge(const BaseCornerEdgeCell* leftCorner, 
        const std::vector<std::unique_ptr<HorizontalEdgeCell>>& edge, 
        const BaseCornerEdgeCell* rightCorner,
        const std::vector<std::unique_ptr<EdgeConnector>>& connectors) const;
        
	void DrawChessboard() const;
};

template <std::ranges::forward_range Range>
int BaseChessboard::CalculateNearestCellIndex(Range&& positions, Vector2 anchoredPosition) const
{
    auto it = std::ranges::min_element(positions, {}, [&](const Vector2& v){
        int deltaRow = v.row - anchoredPosition.row;
        int deltaCol = v.col - anchoredPosition.col;
        return std::tuple{
            deltaRow * deltaRow + deltaCol * deltaCol,
            v.row,
            v.col
        };
    });

    if (it == positions.end())
        return -1;
    else
        return CalculateCellIndex(*it);
}

template <std::predicate<const Vector2&> PrimaryPredicate, std::predicate<const Vector2&> SecondaryPredicate>
int BaseChessboard::CalculateNextMarkedCellIndex(PrimaryPredicate primaryCondition, SecondaryPredicate secondaryCondition, 
    Vector2 anchoredPosition, BaseChessboard::DeltaMove priorityDirection) const 
{
    auto firstFilteredView = _positionsOfMarkedCells | std::views::filter(primaryCondition);

    if (firstFilteredView.empty())
    {
        auto secondFilteredView = _positionsOfMarkedCells | std::views::filter(secondaryCondition);
        if (secondFilteredView.empty())
            return -1;
        else
        {
            switch (priorityDirection)
            {
            case BaseChessboard::DeltaMove::UP:
                anchoredPosition.row = static_cast<int>(_CHESSBOARD_SIZE);
                break;
            case BaseChessboard::DeltaMove::DOWN:
                anchoredPosition.row = -1;
                break;
            case BaseChessboard::DeltaMove::LEFT:
                anchoredPosition.col = static_cast<int>(_CHESSBOARD_SIZE);
                break;
            case BaseChessboard::DeltaMove::RIGHT:
                anchoredPosition.col = -1;
                break;
            }

            return CalculateNearestCellIndex(secondFilteredView, anchoredPosition);
        }
    }
    else
        return CalculateNearestCellIndex(firstFilteredView, anchoredPosition);
}

template <std::derived_from<BaseHorizontalEdgeCell> HorizontalEdgeCell, std::derived_from<BaseEdgeConnector> EdgeConnector>
void BaseChessboard::DrawEdge(const BaseCornerEdgeCell* leftCorner, 
    const std::vector<std::unique_ptr<HorizontalEdgeCell>>& edge, 
    const BaseCornerEdgeCell* rightCorner,
    const std::vector<std::unique_ptr<EdgeConnector>>& connectors) const
{
    for (std::size_t line = 0; line < BaseCornerEdgeCell::HEIGHT; ++line)
    {
        leftCorner->DrawCell(line);
        for (std::size_t cellInLine = 0; cellInLine < _CHESSBOARD_SIZE; ++cellInLine)
        {
            connectors[cellInLine]->DrawCell(line);
            edge[cellInLine]->DrawCell(line);
        }
        connectors[_CHESSBOARD_SIZE]->DrawCell(line);
        rightCorner->DrawCell(line);
        std::wcout << std::endl;
    }
}