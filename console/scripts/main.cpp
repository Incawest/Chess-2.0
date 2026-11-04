#include <fcntl.h>
#include <io.h>
#include <memory>
#include "GameManagement.h"
#include "Pawn.h"
#include "Rook.h"
#include "ShortPieceFormatter.h"
#include "DetailedPieceFormatter.h"

void PrintDescription(const IDescribable& object)
{
    std::wcout << object.Describe().c_str() << std::endl;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::shared_ptr<BaseChessPiece> pieces[] = {std::make_shared<Pawn>(), std::make_shared<Rook>(false)};

    std::wcout << L"-------BINDING-------" << std::endl;
    std::wcout << L"Early: " << pieces[0]->GetClassName().c_str() << std::endl;
    std::wcout << L"Late: " << pieces[0]->Describe().c_str() << std::endl;

    std::wcout << L"-------INTERFACE-------" << std::endl;
    for (const auto& piece : pieces)
    {
        if (auto describable = dynamic_cast<IDescribable*>(piece.get()))
            PrintDescription(*describable);
    }
    auto pawn = dynamic_cast<Pawn*>(pieces[0].get());
    if (pawn)
        std::wcout << L"Derived: " << pawn->GetClassName().c_str() << std::endl;
    std::wcout << L"Rook is Pawn = " << (dynamic_cast<Pawn*>(pieces[1].get()) != nullptr) << std::endl;

    GameManagement gameManagement(8, 5);
    Chessboard& gameChessboard = gameManagement.GetChessboard();
    std::wcout << L"-------RULES-------" << std::endl;
    try
    {
        for (const auto& piece : pieces)
            gameChessboard.AddChessPiece(piece);
        std::wcout << L"Added Pawn and Rook" << std::endl;
    }
    catch (const ChessRuleException& error)
    {
        std::wcout << L"Rule: " << error.what() << std::endl;
    }
    catch (const std::exception& error)
    {
        std::wcout << L"Adding failed: " << error.what() << std::endl;
    }

    auto extraRook = std::make_shared<Rook>();
    try
    {
        gameChessboard.AddChessPiece(extraRook);
    }
    catch (const ChessRuleException& error)
    {
        std::wcout << L"Rule: " << error.what() << std::endl;
    }
    try
    {
        gameChessboard.RemoveChessPiece(extraRook);
    }
    catch (const ChessRuleException& error)
    {
        std::wcout << L"Rule: " << error.what() << std::endl;
    }
    std::wcout << L"White pieces after refusal = " << gameChessboard.GetWhiteChessPieces().size() << std::endl;
    std::wcout << L"-------FORMATTER-------" << std::endl;
    gameManagement.SetPieceFormatter(std::make_unique<ShortPieceFormatter>());
    std::wcout << L"Short: ";
    gameManagement.PrintPieceInfo(*pieces[0]);
    gameManagement.SetPieceFormatter(std::make_unique<DetailedPieceFormatter>());
    std::wcout << L"Detailed: ";
    gameManagement.PrintPieceInfo(*pieces[0]);

    gameChessboard.Update();
    std::wcout << std::endl;
    return 0;
}
