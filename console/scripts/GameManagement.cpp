#include "GameManagement.h"

GameManagement& GameManagement::GetGameManagement() noexcept
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::StartGame()
{
	_chessboard = std::make_shared<BaseChessboard>(8);
	_activePlayer = std::make_unique<Player>(_chessboard, true);
	_inactivePlayer = std::make_unique<Player>(_chessboard, false);

	_activePlayer->ActivateSelection();
}

Vector2 GameManagement::GetSizeOfActiveBlocks() const noexcept
{
	Vector2 sizeOfActiveBlocks{0, 0};
	sizeOfActiveBlocks += _chessboard->GetSizeInChars();
	return sizeOfActiveBlocks;
}

std::vector<TextBlock> GameManagement::GetActiveBlocks() const
{
	std::vector<TextBlock> textBlocks;
	textBlocks.reserve(1);
	textBlocks.emplace_back(_chessboard->BuildTextBlock({}, {}));
	return textBlocks;
}

void GameManagement::Update()
{
	while (_currentGameState != GameState::OFF)
	{
		Blinkable::UpdateAll();

		Console::ResetCaret();
		if(Console::DoesThisFitInConsole(GetSizeOfActiveBlocks()))
			Console::DrawTextBlocks(GetActiveBlocks());
		else
			Console::DrawWstring(L"Not enough space for GUI");

		Console::RefreshConsoleAfterCaret();

		PickUpInput();
	}
}

void GameManagement::PickUpInput()
{
	if (_kbhit())
	{
		int inputCode = _getch();
		if (inputCode == 13)
		{
			if (_currentGameState == GameState::PIECE_SELECTION)
			{
				if (_chessboard->CalculateAllowedMoves())
					_currentGameState = GameState::PATH_SELECTION;
			}
		}
		else if (inputCode == 27)
		{
			if (_currentGameState == GameState::PATH_SELECTION)
			{
				_currentGameState = GameState::PIECE_SELECTION;
				_chessboard->ClearAllowedMoves();
			}
			else
				_currentGameState = GameState::OFF;
		}
		else if (inputCode == 0 || inputCode == 224)
		{
			inputCode = _getch();
			if(inputCode == 98)
				Console::RefreshConsole();
			else if (inputCode == 72)
			{
				if (_currentGameState == GameState::PIECE_SELECTION)
					_activePlayer->GoToNextSelection(Utilits::DeltaMove::UP);
				else if (_currentGameState == GameState::PATH_SELECTION)
					_chessboard->SetNextMarkedCell(Utilits::DeltaMove::UP);
			}
			else if(inputCode == 75)
			{
				if (_currentGameState == GameState::PIECE_SELECTION)
					_activePlayer->GoToNextSelection(Utilits::DeltaMove::LEFT);
				else if (_currentGameState == GameState::PATH_SELECTION)
					_chessboard->SetNextMarkedCell(Utilits::DeltaMove::LEFT);
			}
			else if(inputCode == 77)
			{
				if (_currentGameState == GameState::PIECE_SELECTION)
					_activePlayer->GoToNextSelection(Utilits::DeltaMove::RIGHT);
				else if (_currentGameState == GameState::PATH_SELECTION)
					_chessboard->SetNextMarkedCell(Utilits::DeltaMove::RIGHT);
			}
			else if (inputCode == 80)
			{
				if (_currentGameState == GameState::PIECE_SELECTION)
					_activePlayer->GoToNextSelection(Utilits::DeltaMove::DOWN);
				if (_currentGameState == GameState::PATH_SELECTION)
					_chessboard->SetNextMarkedCell(Utilits::DeltaMove::DOWN);
			}
		}
	}
}