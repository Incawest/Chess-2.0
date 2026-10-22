#pragma once

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
    
    const std::size_t _CHESSBOARD_SIZE;
	bool _isActive;
	std::vector<std::unique_ptr<BaseBoardCell>> _cells;
    ChessboardEdges _edges;

public:
	BaseChessboard(std::size_t chessBoardSize, bool isActive = true);
    virtual ~BaseChessboard();

    std::size_t GetChessboardSize();
    void SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, int col, int row);

	void Update() override;

private:
	void BuildChessboard();

    void DrawEmptyLine(std::size_t length) const;
    template <std::derived_from<BaseHorizontalEdgeCell> HorizontalEdgeCell, std::derived_from<BaseEdgeConnector> EdgeConnector>
    void DrawEdge(const BaseCornerEdgeCell* leftCorner, 
        const std::vector<std::unique_ptr<HorizontalEdgeCell>>& edge, 
        const BaseCornerEdgeCell* rightCorner,
        const std::vector<std::unique_ptr<EdgeConnector>>& connectors) const;
	void DrawChessboard() const;
};

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