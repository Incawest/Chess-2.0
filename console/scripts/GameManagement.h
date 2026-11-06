#pragma once

#include <conio.h>
#include <iostream>
#include <unordered_set>
#include "BaseChessboard.h"
#include "Blinkable.h"
#include "Console.h"
#include "IUpdatable.h"
#include "Player.h"

class GameManagement : public IUpdatable
{
public:
    enum class GameState
    {
        OFF,
        MAIN_MENU,
        PIECE_SELECTION,
        PATH_SELECTION
    };
private:
    GameState _currentGameState = GameState::PIECE_SELECTION;
    static inline int _minRowCnt = 28;
    static inline int _minColCnt = 55;

    std::shared_ptr<BaseChessboard> _chessboard;

    std::unique_ptr<Player> _activePlayer;
    std::unique_ptr<Player> _inactivePlayer;
public:
    static GameManagement& GetGameManagement() noexcept;
    static void SetGUIConfines(int rowCnt, int colCnt);

    GameManagement(const GameManagement& other) = delete;
    GameManagement& operator=(const GameManagement& other) = delete;

    void StartGame();
	void Update() override;

private:
    GameManagement();
    ~GameManagement();
    
    void PickUpInput();
};