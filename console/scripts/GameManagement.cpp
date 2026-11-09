#include "GameManagement.h"

GameManagement& GameManagement::GetGameManagement() noexcept
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::SetGUIConfines(int rowCnt, int colCnt)
{
	_minRowCnt = rowCnt;
	_minColCnt = colCnt + 1;
}

GameManagement::GameManagement() = default;
GameManagement::~GameManagement() = default;

void GameManagement::StartGame()
{
	_chessboard = std::make_shared<BaseChessboard>(8);
	_activePlayer = std::make_unique<Player>(_chessboard, true);
	_inactivePlayer = std::make_unique<Player>(_chessboard, false);

	_activePlayer->ActivateSelection();
}

void GameManagement::Update()
{
	while (_currentGameState != GameState::OFF)
	{
		Console::ResetCaret();
		if (Console::IsThisFitInConsole(_minRowCnt, _minColCnt))
		{
			Blinkable::UpdateAll();
			_chessboard->Update();
		}
		else
			std::wcout << L"Not enough space for GUI\033[J" << std::flush;

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