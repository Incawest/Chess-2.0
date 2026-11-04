#pragma once
#include <conio.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Chessboard.h"
#include "IPieceFormatter.h"

class GameManagement
{
private:
    static constexpr int _FRAME_DELAY_MIL_SEC = 1000;

    std::unique_ptr<Chessboard> _chessboard;
    std::unique_ptr<IPieceFormatter> _pieceFormatter;
    bool _isGameRunning = true;
public:
    GameManagement(int edgeLength, int chessPiecesValue);
    ~GameManagement() noexcept;
    void Update();
    void SetPieceFormatter(std::unique_ptr<IPieceFormatter> formatter);
    void PrintPieceInfo(const BaseChessPiece& piece) const;
    Chessboard& GetChessboard() const;
private:
    void ClearConsole() const;
    void PickUpInput();
};
