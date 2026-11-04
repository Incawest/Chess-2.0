#include "GameManagement.h"

GameManagement::GameManagement()
{
	_mainMenu = std::make_unique<MainMenu>();
	_startGameMenu = std::make_unique<StartGame>();

	_activeWindow = _mainMenu.get();

	Console::RefreshConsole();
}

GameManagement::~GameManagement() = default;

GameManagement& GameManagement::GetGameManagement()
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::ProcessMenuAction(MenuAction action)
{
    switch (action)
    {
	case MenuAction::MainMenu:
		_activeWindow = _mainMenu.get();
		_activeWindow->NowActive();
		break;
    case MenuAction::StartGame:
        _activeWindow = _startGameMenu.get();
		_activeWindow->NowActive();
        break;
    case MenuAction::Exit:
        _isGameRunning = false;
        break;
	default:
		break;
	}
}

void GameManagement::SetGUIConfines(int rowCnt, int colCnt)
{
	_minRowCnt = rowCnt;
	_minColCnt = colCnt + 1;
}

void GameManagement::Update()
{
	bool wasConsoleFit = false;
	while (_isGameRunning)
	{
		Console::ResetCaret();

		bool isConsoleFit = false;
		
		if (_activeWindow != nullptr)
        {
            isConsoleFit = Console::IsThisFitInConsole(
                _activeWindow->GetRequiredHeight(),
                _activeWindow->GetRequiredWidth()
            );
        }

		if (isConsoleFit != wasConsoleFit)
		{
			Console::RefreshConsole();
			wasConsoleFit = isConsoleFit;
		}

		if (isConsoleFit && _activeWindow != nullptr)
		{
			_activeWindow->Update();
		}
		else
			std::wcout << L"Not enough space for GUI\033[J" << std::flush;

		std::this_thread::sleep_for(_FRAME_DELAY_MIL_SEC);

		if (_activeWindow != nullptr)
		{
			if (auto action = _activeWindow->HandleMenuSelect())
        		ProcessMenuAction(*action);
		}
	}
	Console::RefreshConsole();
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