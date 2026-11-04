#include "GameManagement.h"
#include <stdexcept>
#include <utility>
#include "DetailedPieceFormatter.h"

GameManagement::GameManagement(int edgeLength, int maxChessPiecesValue)
{
    _chessboard = std::make_unique<Chessboard>(edgeLength, maxChessPiecesValue);
    _pieceFormatter = std::make_unique<DetailedPieceFormatter>();
    std::wcout << L"GameManagement was created" << std::endl;
}

GameManagement::~GameManagement() noexcept
{
	std::wcout << L"GameManagement was destroyed" << std::endl;
}

Chessboard& GameManagement::GetChessboard() const
{
    return *_chessboard;
}

void GameManagement::Update()
{
	while (_isGameRunning)
	{
	   ClearConsole();
	   _chessboard->Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(_FRAME_DELAY_MIL_SEC));

        PickUpInput();
	}
    std::wcout << std::endl;
}

void GameManagement::ClearConsole() const
{
	std::wcout << L"\033[2J\033[3J\033[1;1H" << std::flush;
}

void GameManagement::PickUpInput()
{
	if (_kbhit())
	{
		if (_getch() == 27)
			_isGameRunning = false;
	}
}

void GameManagement::SetPieceFormatter(std::unique_ptr<IPieceFormatter> formatter)
{
    if (!formatter)
        throw std::invalid_argument("A piece formatter is required.");
    _pieceFormatter = std::move(formatter);
}

void GameManagement::PrintPieceInfo(const BaseChessPiece& piece) const
{
    std::wcout << _pieceFormatter->Format(piece).c_str() << std::endl;
}
