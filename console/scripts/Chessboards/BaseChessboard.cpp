#include "BaseChessboard.h"

BaseChessboard::BaseChessboard(std::size_t chessboardSize): BaseChessboard{chessboardSize, Corners{{
	{ChessboardParts::TOP_LEFT_CORNER, CornerEdgeCell::Type::TOP_LEFT},
	{ChessboardParts::TOP_RIGHT_CORNER, CornerEdgeCell::Type::TOP_RIGHT},
	{ChessboardParts::BOTTOM_LEFT_CORNER, CornerEdgeCell::Type::BOTTOM_LEFT},
	{ChessboardParts::BOTTOM_RIGHT_CORNER, CornerEdgeCell::Type::BOTTOM_RIGHT}
	}}}
{
}

BaseChessboard::BaseChessboard(std::size_t chessboardSize, Corners corners) :
	CHESSBOARD_SIZE{chessboardSize}, CHESSBOARD_SQUARE{CHESSBOARD_SIZE * CHESSBOARD_SIZE}, _edges{.corners = std::move(corners)}
{
	BuildChessboard();
}

std::size_t BaseChessboard::GetChessboardSize() const noexcept
{
	return CHESSBOARD_SIZE;
}

void BaseChessboard::SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, Vector2 position) noexcept
{
	auto realChessPiece = chessPiece.lock();
	if (realChessPiece != nullptr && position.row < CHESSBOARD_SIZE && position.col < CHESSBOARD_SIZE)
	{
		realChessPiece->SetPosition(position);
		_cells[position.row * CHESSBOARD_SIZE + position.col].SetPieceOnCell(chessPiece);
	}
}

void BaseChessboard::SetSelectedCell(Vector2 position)
{
	SetCellSelection(_selectedCellIndex, false);
	if (position.row < CHESSBOARD_SIZE && position.col < CHESSBOARD_SIZE)
	{
		std::size_t index = CalculateCellIndex(position);
		SetCellSelection(index, true);
		_selectedCellIndex = index;
	}
	else
		_selectedCellIndex = -1;
}

void BaseChessboard::SetNextMarkedCell(Utilits::DeltaMove direction)
{
	int nextMarkedIndex = Utilits::FindNextPositionIndex(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedMarkedCellIndex), 
		direction, 
		CHESSBOARD_SIZE);

	int nextGlobalIndex = CalculateCellIndex(_positionsOfMarkedCells[nextMarkedIndex]);

	if (nextGlobalIndex >= 0)
	{
		SetCellSelection(_selectedMarkedCellIndex, false);

		_selectedMarkedCellIndex = nextGlobalIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
}

bool BaseChessboard::CalculateAllowedMoves()
{
	if (_positionsOfMarkedCells.size() > 0)
		ClearAllowedMoves();

	if (_selectedCellIndex < 0)
		return false;

	std::shared_ptr<ChessPiece> selectedChessPiece = _cells[_selectedCellIndex].GetChessPiece();
	if (selectedChessPiece == nullptr)
		return false;

	std::size_t countOfFullPaths = selectedChessPiece->GetCountOfFullPaths();

	Vector2 anchoredPosition = CalculateCellPosition(_selectedCellIndex);
	std::span<const ChessPiece::MovePosition> _fullPathForMove;
	for (int i = 0; i < countOfFullPaths; ++i)
	{
		_fullPathForMove = selectedChessPiece->GetFullPathForMove(i);
		for (const auto& el : _fullPathForMove)
		{
			Vector2 elPosition = anchoredPosition + el.GetPosition();
			if (!(elPosition.row >= 0 && elPosition.col >= 0 && elPosition.row < CHESSBOARD_SIZE && elPosition.col < CHESSBOARD_SIZE))
				break;

			std::shared_ptr<ChessPiece> potentOppositePiece = _cells[CalculateCellIndex(elPosition)].GetChessPiece();
			
			if (potentOppositePiece != nullptr)
			{
				if (potentOppositePiece->GetIsWhite() != selectedChessPiece->GetIsWhite())
					_positionsOfMarkedCells.push_back(elPosition);
				break;
			}
			else if (el.GetIsMoveForCapturingPieceOnly())
				break;

			_positionsOfMarkedCells.push_back(elPosition);
		}
	}
	if (_positionsOfMarkedCells.size() > 0)
	{
		SortPositionsOfMarkedCells();
		SetMarkAlongEntireVectorOfMarkedCells(true);
		return true;
	}
	else 
		return false;
}

void BaseChessboard::ClearAllowedMoves()
{
	SetMarkAlongEntireVectorOfMarkedCells(false);
	_positionsOfMarkedCells.clear();
}

void BaseChessboard::Update()
{
	DrawChessboard();
}

void BaseChessboard::BuildChessboard()
{
	_edges.topHorizontalEdge.reserve(CHESSBOARD_SIZE);
	_edges.bottomHorizontalEdge.reserve(CHESSBOARD_SIZE);
	_edges.leftVerticalEdge.reserve(CHESSBOARD_SIZE);
	_edges.rightVerticalEdge.reserve(CHESSBOARD_SIZE);

	_cells.resize(CHESSBOARD_SIZE * CHESSBOARD_SIZE);

	const std::size_t CHESSBOARD_SIZE_ONE_LARGER = CHESSBOARD_SIZE + 1;
	_edges.topEdgeConnectors.reserve(CHESSBOARD_SIZE_ONE_LARGER);
	_edges.bottomEdgeConnectors.reserve(CHESSBOARD_SIZE_ONE_LARGER);

	wchar_t firstMarkedLetter = 'A', currentMarkedLetter;
	for (std::size_t i = 0, rowNumber; i < CHESSBOARD_SIZE; ++i)
	{
		rowNumber = CHESSBOARD_SIZE - i;
		currentMarkedLetter = firstMarkedLetter + i;

		_edges.topHorizontalEdge.emplace_back(ChessboardParts::TOP_BORDER, currentMarkedLetter, HorizontalEdgeCell::Type::TOP);
		_edges.bottomHorizontalEdge.emplace_back(ChessboardParts::BOTTOM_BORDER, currentMarkedLetter, HorizontalEdgeCell::Type::BOTTOM);
		_edges.leftVerticalEdge.emplace_back(ChessboardParts::LEFT_BORDER, rowNumber, VerticalEdgeCell::Type::LEFT);
		_edges.rightVerticalEdge.emplace_back(ChessboardParts::RIGHT_BORDER, rowNumber, VerticalEdgeCell::Type::RIGHT);
	}

	for (std::size_t i = 0; i < CHESSBOARD_SIZE_ONE_LARGER; ++i)
	{
		_edges.topEdgeConnectors.emplace_back(ChessboardParts::TOP_BORDER, EdgeConnector::Type::TOP);
		_edges.bottomEdgeConnectors.emplace_back(ChessboardParts::BOTTOM_BORDER, EdgeConnector::Type::BOTTOM);
	}
}

void BaseChessboard::SetCellSelection(std::size_t cellIndex, bool isSelected)
{
	if (cellIndex < CHESSBOARD_SQUARE)
	{
		Vector2 position = CalculateCellPosition(cellIndex);
		_cells[cellIndex].SetSelection(isSelected);
		SetEdgesSelection(position, isSelected);
	}
}

void BaseChessboard::SetEdgesSelection(Vector2 intersection, bool isSelected)
{
	_edges.topHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.bottomHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.leftVerticalEdge[intersection.row].SetSelection(isSelected);
	_edges.rightVerticalEdge[intersection.row].SetSelection(isSelected);
}

void BaseChessboard::SetEdgesSelection(std::size_t intersectionIndex, bool isSelected)
{
	SetEdgesSelection(CalculateCellPosition(intersectionIndex), isSelected);
}

void BaseChessboard::SetMarkAlongEntireVectorOfMarkedCells(bool isMarked)
{

	for (const Vector2& el : _positionsOfMarkedCells)
		_cells[CalculateCellIndex(el)].SetMark(isMarked);

	Vector2 piecePosition = CalculateCellPosition(_selectedCellIndex);
	int nearestMarkedIndex = Utilits::FindNextPositionIndex(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedCellIndex), 
		Utilits::DeltaMove::UP, 
		CHESSBOARD_SIZE);
	int nearestGlobalIndex = CalculateCellIndex(_positionsOfMarkedCells[nearestMarkedIndex]);
		
	if (isMarked && nearestGlobalIndex >= 0)
	{
		SetEdgesSelection(_selectedCellIndex, false);

		_selectedMarkedCellIndex = nearestGlobalIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
	else if (_selectedMarkedCellIndex >= 0)
	{
		SetCellSelection(_selectedMarkedCellIndex, false);
		_selectedMarkedCellIndex = -1;
		
		SetEdgesSelection(_selectedCellIndex, true);
	}
}

inline Vector2 BaseChessboard::CalculateCellPosition(std::size_t cellIndex) const noexcept
{
	return Vector2{static_cast<int>(cellIndex / CHESSBOARD_SIZE), static_cast<int>(cellIndex % CHESSBOARD_SIZE)};
}

inline std::size_t BaseChessboard::CalculateCellIndex(Vector2 cellPosition) const noexcept
{
	return cellPosition.row * CHESSBOARD_SIZE + cellPosition.col;
}

void BaseChessboard::SortPositionsOfMarkedCells()
{
	std::ranges::sort(_positionsOfMarkedCells, {}, [](const Vector2& v){
		return std::tie(v.row, v.col);
	});
}

void BaseChessboard::DrawEdge(const CornerEdgeCell* leftCorner, 
    const std::vector<HorizontalEdgeCell>& edge, 
    const CornerEdgeCell* rightCorner,
    const std::vector<EdgeConnector>& connectors) const
{
    for (std::size_t line = 0; line < CornerEdgeCell::HEIGHT; ++line)
    {
        leftCorner->DrawCell(line);
        for (std::size_t cellInLine = 0; cellInLine < CHESSBOARD_SIZE; ++cellInLine)
        {
            connectors[cellInLine].DrawCell(line);
            edge[cellInLine].DrawCell(line);
        }
        connectors[CHESSBOARD_SIZE].DrawCell(line);
        rightCorner->DrawCell(line);
        std::wcout << std::endl;
    }
}

void BaseChessboard::DrawChessboard() const
{
	Console::SetTextColor(&Color::WHITE);
	Console::SetBGColor(&Color::GRAY);
	
	DrawEdge(&_edges.corners[0], _edges.topHorizontalEdge, &_edges.corners[1], _edges.topEdgeConnectors);

	for (std::size_t cellRow = 0; cellRow < CHESSBOARD_SIZE; ++cellRow)
	{
		std::size_t rowOffset = cellRow * CHESSBOARD_SIZE;
		for (std::size_t line = 0; line < BaseBoardCell::HEIGHT; ++line)
		{
			_edges.leftVerticalEdge[cellRow].DrawCell(line);

			for (std::size_t cellInRow = 0; cellInRow < CHESSBOARD_SIZE; ++cellInRow)
			{
				Utilits::DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
				_cells[rowOffset + cellInRow].DrawCell(line);
			}

			Utilits::DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
			_edges.rightVerticalEdge[cellRow].DrawCell(line);
			std::wcout << std::endl;
		}
	}
	
	DrawEdge(&_edges.corners[2], _edges.bottomHorizontalEdge, &_edges.corners[3], _edges.bottomEdgeConnectors);

	Console::ResetConsoleColor();
}