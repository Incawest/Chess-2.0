#include "BaseChessboard.h"

BaseChessboard::ChessboardParts::~ChessboardParts() = default;

BaseChessboard::BaseChessboard(std::size_t boardSize, bool isActive): _chessBoardSize{boardSize}, _isActive{isActive}
{
	BuildChessboard();
}

BaseChessboard::~BaseChessboard() = default;

void BaseChessboard::Update()
{
	if (_isActive)
	{
		DrawChessboard();
	}
}

void BaseChessboard::BuildChessboard()
{
	_edges.corners.resize(4);
	_edges.corners[0] = std::make_unique<TopLeftCornerEdgeCell>(ChessboardParts::TOP_LEFT_CORNER);
	_edges.corners[1] = std::make_unique<TopRightCornerEdgeCell>(ChessboardParts::TOP_RIGHT_CORNER);
	_edges.corners[2] = std::make_unique<BottomLeftCornerEdgeCell>(ChessboardParts::BOTTOM_LEFT_CORNER);
	_edges.corners[3] = std::make_unique<BottomRightCornerEdgeCell>(ChessboardParts::BOTTOM_RIGHT_CORNER);

	_edges.topHorizontalEdge.resize(_chessBoardSize);
	_edges.bottomHorizontalEdge.resize(_chessBoardSize);
	_edges.leftVerticalEdge.resize(_chessBoardSize);
	_edges.rightVerticalEdge.resize(_chessBoardSize);

	_cells.resize(_chessBoardSize * _chessBoardSize);

	const std::size_t CHESSBOARD_SIZE_ONE_LARGER = _chessBoardSize + 1;
	_edges.topEdgeConnectors.resize(CHESSBOARD_SIZE_ONE_LARGER);
	_edges.bottomEdgeConnectors.resize(CHESSBOARD_SIZE_ONE_LARGER);

	wchar_t firstMarkedLetter = 'A', currentMarkedLetter;
	for (std::size_t i = 0, rowNumber; i < _chessBoardSize; ++i)
	{
		rowNumber = _chessBoardSize - i;
		currentMarkedLetter = firstMarkedLetter + i;

		_edges.topHorizontalEdge[i] = std::make_unique<TopHorizontalEdgeCell>(ChessboardParts::TOP_BORDER, currentMarkedLetter);
		_edges.bottomHorizontalEdge[i] = std::make_unique<BottomHorizontalEdgeCell>(ChessboardParts::BOTTOM_BORDER, currentMarkedLetter);
		_edges.leftVerticalEdge[i] = std::make_unique<LeftVerticalEdgeCell>(ChessboardParts::LEFT_BORDER, rowNumber);
		_edges.rightVerticalEdge[i] = std::make_unique<RightVerticalEdgeCell>(ChessboardParts::RIGHT_BORDER, rowNumber);

		const std::size_t ROW_OFFSET = i * _chessBoardSize;
	    for (std::size_t j = 0; j < _chessBoardSize; ++j)
	    {
	        _cells[ROW_OFFSET + j] = std::make_unique<BaseBoardCell>();
	    }
	}

	for (std::size_t i = 0; i < CHESSBOARD_SIZE_ONE_LARGER; ++i)
	{
		_edges.topEdgeConnectors[i] = std::make_unique<TopEdgeConnector>(ChessboardParts::TOP_BORDER);
		_edges.bottomEdgeConnectors[i] = std::make_unique<BottomEdgeConnector>(ChessboardParts::BOTTOM_BORDER);
	}
}

void BaseChessboard::DrawChessboard() const
{
	Console::SetTextColor(&Color::WHITE);
	Console::SetBGColor(&Color::GRAY);
	
	DrawEdge(_edges.corners[0].get(), _edges.topHorizontalEdge, _edges.corners[1].get(), _edges.topEdgeConnectors);

	for (std::size_t cellRow = 0; cellRow < _chessBoardSize; ++cellRow)
	{
		for (std::size_t line = 0; line < BaseBoardCell::HEIGHT; ++line)
		{
			_edges.leftVerticalEdge[cellRow]->DrawCell(line);

			std::size_t rowOffset = cellRow * _chessBoardSize;
			for (std::size_t cellInRow = 0; cellInRow < _chessBoardSize; ++cellInRow)
			{
				std::wcout << L' ';
				_cells[rowOffset + cellInRow]->DrawCell(line);
			}

			std::wcout << L' ';
			_edges.rightVerticalEdge[cellRow]->DrawCell(line);
			std::wcout << std::endl;
		}
	}
	
	DrawEdge(_edges.corners[2].get(), _edges.bottomHorizontalEdge, _edges.corners[3].get(), _edges.bottomEdgeConnectors);

	Console::ResetConsoleColor();
}