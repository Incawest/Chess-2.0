#include "GameManagement.h"
GameManagement::GameManagement()
{
	_chessboard = new Chessboard(8);
}

GameManagement::~GameManagement()
{
	delete _chessboard;
}

GameManagement& GameManagement::GetGameManagement()
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::SetGUIConfines(int rowCnt, int colCnt)
{
	_minRowCnt = rowCnt;
	_minColCnt = colCnt + 1;
}

void GameManagement::Update()
{
	while (_isGameRunning)
	{
		Console::ResetCaret();
		if (Console::IsThisFitInConsole(_minRowCnt, _minColCnt))
		{
			_chessboard->Update();
		}
		else
			std::wcout << L"Not enough space for GUI\033[J" << std::flush;

		std::this_thread::sleep_for(_FRAME_DELAY_MIL_SEC);
		PickUpInput();
	}
}

void GameManagement::PickUpInput()
{
	if (_kbhit())
	{
		int inputCode = _getch();
		if (inputCode == 27)
			_isGameRunning = false;
		else if (inputCode == 0 || inputCode == 224)
		{
			inputCode = _getch();
			if(inputCode == 98)
				Console::RefreshConsole();
		}
	}
}