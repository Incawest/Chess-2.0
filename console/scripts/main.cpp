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

    GameManagement gameManagement(8, 10);
    Chessboard& gameChessboard = gameManagement.GetChessboard();
    for (const auto& piece : pieces)
        gameChessboard.AddChessPiece(piece);
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
