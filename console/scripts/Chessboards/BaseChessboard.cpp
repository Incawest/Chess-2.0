#include "BaseChessboard.h"

BaseChessboard::ChessboardParts::~ChessboardParts() = default;

BaseChessboard::BaseChessboard(std::size_t boardSize, bool isActive): _CHESSBOARD_SIZE{boardSize}, _isActive{isActive}
{
	BuildChessboard();
}

BaseChessboard::~BaseChessboard() = default;

std::size_t BaseChessboard::GetChessboardSize()
{
	return _CHESSBOARD_SIZE;
}

void BaseChessboard::SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, int col, int row)
{
	auto realChessPiece = chessPiece.lock();
	if (realChessPiece != nullptr && col < _CHESSBOARD_SIZE && row < _CHESSBOARD_SIZE)
	{
		realChessPiece->SetPosition(col, row);
		_cells[row * _CHESSBOARD_SIZE + col]->SetPieceOnCell(chessPiece);
	}
}

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

	_edges.topHorizontalEdge.resize(_CHESSBOARD_SIZE);
	_edges.bottomHorizontalEdge.resize(_CHESSBOARD_SIZE);
	_edges.leftVerticalEdge.resize(_CHESSBOARD_SIZE);
	_edges.rightVerticalEdge.resize(_CHESSBOARD_SIZE);

	_cells.resize(_CHESSBOARD_SIZE * _CHESSBOARD_SIZE);

	const std::size_t CHESSBOARD_SIZE_ONE_LARGER = _CHESSBOARD_SIZE + 1;
	_edges.topEdgeConnectors.resize(CHESSBOARD_SIZE_ONE_LARGER);
	_edges.bottomEdgeConnectors.resize(CHESSBOARD_SIZE_ONE_LARGER);

	wchar_t firstMarkedLetter = 'A', currentMarkedLetter;
	for (std::size_t i = 0, rowNumber; i < _CHESSBOARD_SIZE; ++i)
	{
		rowNumber = _CHESSBOARD_SIZE - i;
		currentMarkedLetter = firstMarkedLetter + i;

		_edges.topHorizontalEdge[i] = std::make_unique<TopHorizontalEdgeCell>(ChessboardParts::TOP_BORDER, currentMarkedLetter);
		_edges.bottomHorizontalEdge[i] = std::make_unique<BottomHorizontalEdgeCell>(ChessboardParts::BOTTOM_BORDER, currentMarkedLetter);
		_edges.leftVerticalEdge[i] = std::make_unique<LeftVerticalEdgeCell>(ChessboardParts::LEFT_BORDER, rowNumber);
		_edges.rightVerticalEdge[i] = std::make_unique<RightVerticalEdgeCell>(ChessboardParts::RIGHT_BORDER, rowNumber);

		const std::size_t ROW_OFFSET = i * _CHESSBOARD_SIZE;
	    for (std::size_t j = 0; j < _CHESSBOARD_SIZE; ++j)
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

void BaseChessboard::DrawEmptyLine(std::size_t length) const
{
	for (std::size_t i = 0; i < length; ++i)
		std::wcout << L' ';
}

void BaseChessboard::DrawChessboard() const
{
	Console::SetTextColor(&Color::WHITE);
	Console::SetBGColor(&Color::GRAY);
	
	DrawEdge(_edges.corners[0].get(), _edges.topHorizontalEdge, _edges.corners[1].get(), _edges.topEdgeConnectors);

	for (std::size_t cellRow = 0; cellRow < _CHESSBOARD_SIZE; ++cellRow)
	{
		for (std::size_t line = 0; line < BaseBoardCell::HEIGHT; ++line)
		{
			_edges.leftVerticalEdge[cellRow]->DrawCell(line);

			std::size_t rowOffset = cellRow * _CHESSBOARD_SIZE;
			for (std::size_t cellInRow = 0; cellInRow < _CHESSBOARD_SIZE; ++cellInRow)
			{
				DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
				_cells[rowOffset + cellInRow]->DrawCell(line);
			}

			DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
			_edges.rightVerticalEdge[cellRow]->DrawCell(line);
			std::wcout << std::endl;
		}
	}
	
	DrawEdge(_edges.corners[2].get(), _edges.bottomHorizontalEdge, _edges.corners[3].get(), _edges.bottomEdgeConnectors);

	Console::ResetConsoleColor();
}