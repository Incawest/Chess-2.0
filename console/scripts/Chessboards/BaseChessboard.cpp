#include "BaseChessboard.h"

BaseChessboard::ChessboardParts::~ChessboardParts() = default;

BaseChessboard::BaseChessboard(std::size_t boardSize): 
	_CHESSBOARD_SIZE{boardSize}, _CHESSBOARD_SQUARE{_CHESSBOARD_SIZE * _CHESSBOARD_SIZE}
{
	BuildChessboard();
}

BaseChessboard::~BaseChessboard() = default;

std::size_t BaseChessboard::GetChessboardSize() const noexcept
{
	return _CHESSBOARD_SIZE;
}

std::size_t BaseChessboard:: GetAllowedMovesCount() const noexcept
{
	return _positionsOfMarkedCells.size();
}

void BaseChessboard::SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, Vector2 position) noexcept
{
	auto realChessPiece = chessPiece.lock();
	if (realChessPiece != nullptr && position.row < _CHESSBOARD_SIZE && position.col < _CHESSBOARD_SIZE)
	{
		realChessPiece->SetPosition(position);
		_cells[position.row * _CHESSBOARD_SIZE + position.col]->SetPieceOnCell(chessPiece);
	}
}

void BaseChessboard::SetSelectedCell(Vector2 position)
{
	SetCellSelection(_selectedCellIndex, false);
	if (position.row < _CHESSBOARD_SIZE && position.col < _CHESSBOARD_SIZE)
	{
		std::size_t index = CalculateCellIndex(position);
		SetCellSelection(index, true);
		_selectedCellIndex = index;
	}
	else
		_selectedCellIndex = -1;
}

void BaseChessboard::SetNextMarkedCell(BaseChessboard::DeltaMove deltaMove)
{
	Vector2 anchoredPosition = CalculateCellPosition(_selectedMarkedCellIndex);
	int nextSelectedCellIndex;
    if (deltaMove == BaseChessboard::DeltaMove::UP || deltaMove == BaseChessboard::DeltaMove::DOWN)
    {
        auto predicateForRowsAboveAnchoredOne = [&anchoredPosition](const Vector2& v){
            return v.row < anchoredPosition.row;
        };
        auto predicateForRowsBelowAnchoredOne = [&anchoredPosition](const Vector2& v){
            return v.row > anchoredPosition.row;
        };
        nextSelectedCellIndex = deltaMove == BaseChessboard::DeltaMove::UP ? 
            CalculateNextMarkedCellIndex(predicateForRowsAboveAnchoredOne, predicateForRowsBelowAnchoredOne, 
				anchoredPosition, deltaMove) :
            CalculateNextMarkedCellIndex(predicateForRowsBelowAnchoredOne, predicateForRowsAboveAnchoredOne, 
				anchoredPosition, deltaMove);
    }
    else
    {
        auto predicateForColumnsToLeftAnchoredOne = [&anchoredPosition](const Vector2& v){
            return v.row == anchoredPosition.row && v.col < anchoredPosition.col;
        };
        auto predicateForColumnsToRightAnchoredOne = [&anchoredPosition](const Vector2& v){
            return v.row == anchoredPosition.row && v.col > anchoredPosition.col;
        };
        nextSelectedCellIndex = deltaMove == BaseChessboard::DeltaMove::LEFT ?
            CalculateNextMarkedCellIndex(predicateForColumnsToLeftAnchoredOne, predicateForColumnsToRightAnchoredOne,
				anchoredPosition, deltaMove) :
            CalculateNextMarkedCellIndex(predicateForColumnsToRightAnchoredOne, predicateForColumnsToLeftAnchoredOne,
				anchoredPosition, deltaMove);
    }

	if (nextSelectedCellIndex >= 0)
	{
		SetCellSelection(_selectedMarkedCellIndex, false);

		_selectedMarkedCellIndex = nextSelectedCellIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
}

void BaseChessboard::CalculateAllowedMoves()
{
	if (_positionsOfMarkedCells.size() > 0)
		ClearAllowedMoves();

	if (_selectedCellIndex < 0)
		return;

	std::shared_ptr<ChessPiece> selectedChessPiece = _cells[_selectedCellIndex]->GetChessPiece();
	if (selectedChessPiece == nullptr)
		return;
	std::size_t countOfFullPaths = selectedChessPiece->GetCountOfFullPaths();

	Vector2 anchoredPosition = CalculateCellPosition(_selectedCellIndex);
	std::vector<ChessPiece::MovePosition> _fullPathForMove;
	for (int i = 0; i < countOfFullPaths; ++i)
	{
		_fullPathForMove = selectedChessPiece->GetFullPathForMove(i, anchoredPosition);
		for (const auto& el : _fullPathForMove)
		{
			Vector2 elPosition = el.GetPosition();
			if (!(elPosition.row < _CHESSBOARD_SIZE && elPosition.col < _CHESSBOARD_SIZE))
				break;

			std::shared_ptr<ChessPiece> potentOppositePiece = _cells[CalculateCellIndex(el.GetPosition())]->GetChessPiece();
			
			if (potentOppositePiece != nullptr)
			{
				if (potentOppositePiece->GetIsWhite() != selectedChessPiece->GetIsWhite())
					_positionsOfMarkedCells.push_back(el.GetPosition());
				break;
			}
			else if (el.GetIsMoveForCapturingPieceOnly())
				break;

			_positionsOfMarkedCells.push_back(el.GetPosition());
		}
	}

	SortPositionsOfMarkedCells();
	SetMarkAlongEntireVectorOfMarkedCells(true);
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

void BaseChessboard::SetCellSelection(std::size_t cellIndex, bool isSelected)
{
	if (cellIndex < _CHESSBOARD_SQUARE)
	{
		Vector2 position = CalculateCellPosition(cellIndex);
		_cells[cellIndex]->SetSelection(isSelected);
		SetEdgesSelection(position, isSelected);
	}
}

void BaseChessboard::SetEdgesSelection(Vector2 intersection, bool isSelected)
{
	_edges.topHorizontalEdge[intersection.col]->SetSelection(isSelected);
	_edges.bottomHorizontalEdge[intersection.col]->SetSelection(isSelected);
	_edges.leftVerticalEdge[intersection.row]->SetSelection(isSelected);
	_edges.rightVerticalEdge[intersection.row]->SetSelection(isSelected);
}

void BaseChessboard::SetEdgesSelection(std::size_t intersectionIndex, bool isSelected)
{
	SetEdgesSelection(CalculateCellPosition(intersectionIndex), isSelected);
}

void BaseChessboard::SetMarkAlongEntireVectorOfMarkedCells(bool isMarked)
{
	auto filteredIndicesView = std::views::iota(0u, _cells.size()) | std::views::filter([this](std::size_t index){
		return std::ranges::binary_search(_positionsOfMarkedCells, index, {}, [this](const Vector2& position) {
			return CalculateCellIndex(position);
		});
	});

	for(std::size_t index : filteredIndicesView)
		_cells[index]->SetMark(isMarked);

	Vector2 piecePosition = CalculateCellPosition(_selectedCellIndex);
	int nearestIndex = CalculateNearestCellIndex(_positionsOfMarkedCells, piecePosition);
		
	if (isMarked && nearestIndex >= 0)
	{
		SetEdgesSelection(_selectedCellIndex, false);

		_selectedMarkedCellIndex = nearestIndex;
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
	return Vector2{static_cast<int>(cellIndex / _CHESSBOARD_SIZE), static_cast<int>(cellIndex % _CHESSBOARD_SIZE)};
}

inline std::size_t BaseChessboard::CalculateCellIndex(Vector2 cellPosition) const noexcept
{
	return cellPosition.row * _CHESSBOARD_SIZE + cellPosition.col;
}

void BaseChessboard::SortPositionsOfMarkedCells()
{
	std::ranges::sort(_positionsOfMarkedCells, {}, [](const Vector2& v){
		return std::tie(v.row, v.col);
	});
}

void BaseChessboard::DrawChessboard() const
{
	Console::SetTextColor(&Color::WHITE);
	Console::SetBGColor(&Color::GRAY);
	
	DrawEdge(_edges.corners[0].get(), _edges.topHorizontalEdge, _edges.corners[1].get(), _edges.topEdgeConnectors);

	for (std::size_t cellRow = 0; cellRow < _CHESSBOARD_SIZE; ++cellRow)
	{
		std::size_t rowOffset = cellRow * _CHESSBOARD_SIZE;
		for (std::size_t line = 0; line < BaseBoardCell::HEIGHT; ++line)
		{
			_edges.leftVerticalEdge[cellRow]->DrawCell(line);

			for (std::size_t cellInRow = 0; cellInRow < _CHESSBOARD_SIZE; ++cellInRow)
			{
				Utilits::DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
				_cells[rowOffset + cellInRow]->DrawCell(line);
			}

			Utilits::DrawEmptyLine(CellsConfiguration::SPACE_BETWEEN_CELLS);
			_edges.rightVerticalEdge[cellRow]->DrawCell(line);
			std::wcout << std::endl;
		}
	}
	
	DrawEdge(_edges.corners[2].get(), _edges.bottomHorizontalEdge, _edges.corners[3].get(), _edges.bottomEdgeConnectors);

	Console::ResetConsoleColor();
}