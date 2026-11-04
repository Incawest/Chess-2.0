#include "Chessboard.h"

Chessboard::Chessboard(int edgeLength, int maxChessPiecesValue) : _edgeLength{edgeLength}, _maxChessPiecesValue{maxChessPiecesValue}
{
    if (edgeLength <= 0 || maxChessPiecesValue < 0)
        throw std::invalid_argument("Invalid chessboard dimensions or piece value limit.");
    _wcharChessboard.resize(_edgeLength * _edgeLength, ' ');
    std::wcout << L"Chessboard was created" << std::endl;
}

Chessboard::~Chessboard() noexcept
{
    std::wcout << L"Chessboard was destroyed" << std::endl;
}

std::vector<std::weak_ptr<BaseChessPiece>> Chessboard::GetWhiteChessPieces() const
{
    return _whiteChessPieces;
}

std::vector<std::weak_ptr<BaseChessPiece>> Chessboard::GetBlackChessPieces() const
{
    return _blackChessPieces;
}

void Chessboard::AddChessPiece(const std::weak_ptr<BaseChessPiece>& weakNewChessPiece)
{
    auto newChessPiece = GetRealPointerOfChessPiece(weakNewChessPiece);
    bool isWhitePiece = newChessPiece->GetIsWhitePiece();
    int chessPieceValue = newChessPiece->GetChessPieceValue();
    int& curChessPiecesValue = isWhitePiece ? _whiteChessPiecesValue : _blackChessPiecesValue;
    auto& weakCurChessPieces = isWhitePiece ? _whiteChessPieces : _blackChessPieces;

    auto existingPiece = std::find_if(weakCurChessPieces.begin(), weakCurChessPieces.end(),
        [this, &newChessPiece](const std::weak_ptr<BaseChessPiece>& item) {
            return GetRealPointerOfChessPiece(item) == newChessPiece;
        });
    if (existingPiece != weakCurChessPieces.end())
        throw ChessRuleException("The piece is already on the chessboard.");
    if (chessPieceValue > _maxChessPiecesValue - curChessPiecesValue)
        throw ChessRuleException("The piece value limit is exceeded.");

    int pieceIndex = isWhitePiece ? 0 : static_cast<int>(_wcharChessboard.size()) - 1;
    if (!weakCurChessPieces.empty())
        pieceIndex = GetRealPointerOfChessPiece(weakCurChessPieces.back())->GetIndexInChessboard()
            + (isWhitePiece ? 1 : -1);
    if (pieceIndex < 0 || pieceIndex >= static_cast<int>(_wcharChessboard.size()) || _wcharChessboard[pieceIndex] != L' ')
        throw ChessRuleException("There is no free cell for the piece.");

    newChessPiece->SetIndexInChessboard(pieceIndex);
    weakCurChessPieces.push_back(weakNewChessPiece);
    curChessPiecesValue += chessPieceValue;
    _wcharChessboard[pieceIndex] = newChessPiece->GetWcharChessPiece();
}

void Chessboard::RemoveChessPiece(const std::weak_ptr<BaseChessPiece>& weakRemovingChessPiece)
{
    auto removingChessPiece = GetRealPointerOfChessPiece(weakRemovingChessPiece);
    bool isWhitePiece = removingChessPiece->GetIsWhitePiece();
    auto& weakCurChessPieces = isWhitePiece ? _whiteChessPieces : _blackChessPieces;
    auto necessaryPiece = std::find_if(weakCurChessPieces.begin(), weakCurChessPieces.end(),
        [this, &removingChessPiece](const std::weak_ptr<BaseChessPiece>& item) {
            return GetRealPointerOfChessPiece(item) == removingChessPiece;
        });
    if (necessaryPiece == weakCurChessPieces.end())
        throw ChessRuleException("The piece is not on the chessboard.");

    int index = removingChessPiece->GetIndexInChessboard();
    for (auto it = std::next(necessaryPiece); it != weakCurChessPieces.end(); ++it)
    {
        auto piece = GetRealPointerOfChessPiece(*it);
        _wcharChessboard[index] = piece->GetWcharChessPiece();
        piece->SetIndexInChessboard(index);
        index += isWhitePiece ? 1 : -1;
    }
    _wcharChessboard[index] = L' ';
    weakCurChessPieces.erase(necessaryPiece);
    int& curChessPiecesValue = isWhitePiece ? _whiteChessPiecesValue : _blackChessPiecesValue;
    curChessPiecesValue -= removingChessPiece->GetChessPieceValue();
    removingChessPiece->SetIndexInChessboard(-1);
}

void Chessboard::Update() const
{
    PrintChessboard();
}

void Chessboard::PrintChessboard() const
{
	std::wcout << Parts::TOP_LEFT_CORNER;
	std::wcout << std::wstring(_edgeLength, Parts::HORIZONTAL_BORDER);
	std::wcout << Parts::TOP_RIGHT_CORNER << std::endl;

	for (int i = 0; i < _edgeLength; ++i)
	{
		std::wcout << Parts::VERTICAL_BORDER;
		std::copy(_wcharChessboard.begin() + i * _edgeLength, _wcharChessboard.begin() + (i + 1) * _edgeLength, std::ostream_iterator<wchar_t, wchar_t>(std::wcout));
		std::wcout << Parts::VERTICAL_BORDER << std::endl;
	}

	std::wcout << Parts::BOTTOM_LEFT_CORNER;
	std::wcout << std::wstring(_edgeLength, Parts::HORIZONTAL_BORDER);
	std::wcout << Parts::BOTTOM_RIGHT_CORNER << std::flush;
}

std::shared_ptr<BaseChessPiece> Chessboard::GetRealPointerOfChessPiece(const std::weak_ptr<BaseChessPiece>& weakChessPiece) const
{
    auto realChessPiece = weakChessPiece.lock();
    if (realChessPiece == nullptr)
        throw std::runtime_error("GetRealPointerOfChessPiece has got a empty pointer.");
    return realChessPiece;
}
