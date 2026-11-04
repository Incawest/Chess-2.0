using System.Collections.Generic;
using System.Linq;

public class Chessboard
{
    private static class Parts
    {
        public const char HORIZONTAL_BORDER = '\u2550';
        public const char VERTICAL_BORDER = '\u2551';
        public const char TOP_LEFT_CORNER = '\u2554';
        public const char TOP_RIGHT_CORNER = '\u2557';
        public const char BOTTOM_LEFT_CORNER = '\u255A';
        public const char BOTTOM_RIGHT_CORNER = '\u255D';
    };

    private int _edgeLength;

    private int _maxChessPiecesValue;
    private int _whiteChessPiecesValue = 0;
    private int _blackChessPiecesValue = 0;
    private List<char> _charChessboard;

    public List<BaseChessPiece> WhiteChessPieces { get; private set; } = new List<BaseChessPiece>();
    public List<BaseChessPiece> BlackChessPieces { get; private set; } = new List<BaseChessPiece>();

    public Chessboard(int edgeLength, int maxChessPiecesValue)
    {
        if (edgeLength <= 0 || maxChessPiecesValue < 0)
            throw new ArgumentException("Invalid chessboard dimensions or piece value limit.");
        _edgeLength = edgeLength;
        _maxChessPiecesValue = maxChessPiecesValue;

        _charChessboard = Enumerable.Repeat(' ', edgeLength * edgeLength).ToList();
    }
    public void AddChessPiece(BaseChessPiece newChessPiece)
    {
        if (newChessPiece is null)
            throw new ArgumentNullException(nameof(newChessPiece));
        ref int curChessPiecesValue = ref (newChessPiece.IsWhitePiece ? ref _whiteChessPiecesValue : ref _blackChessPiecesValue);
        List<BaseChessPiece> curChessPieces = newChessPiece.IsWhitePiece ? WhiteChessPieces : BlackChessPieces;

        if (curChessPieces.Any(piece => ReferenceEquals(piece, newChessPiece)))
            throw new ChessRuleException("The piece is already on the chessboard.");
        if (newChessPiece.ChessPieceValue > _maxChessPiecesValue - curChessPiecesValue)
            throw new ChessRuleException("The piece value limit is exceeded.");

        int pieceIndex = newChessPiece.IsWhitePiece ? 0 : _charChessboard.Count - 1;
        if (curChessPieces.Count != 0)
            pieceIndex = curChessPieces[curChessPieces.Count - 1].IndexInChessboard + (newChessPiece.IsWhitePiece ? 1 : -1);
        if (pieceIndex < 0 || pieceIndex >= _charChessboard.Count || _charChessboard[pieceIndex] != ' ')
            throw new ChessRuleException("There is no free cell for the piece.");

        newChessPiece.IndexInChessboard = pieceIndex;
        curChessPieces.Add(newChessPiece);
        curChessPiecesValue += newChessPiece.ChessPieceValue;
        _charChessboard[pieceIndex] = newChessPiece.CharChessPiece;
    }
    public void RemoveChessPiece(BaseChessPiece removingChessPiece)
    {
        if (removingChessPiece is null)
            throw new ArgumentNullException(nameof(removingChessPiece));
        List<BaseChessPiece> curChessPieces = removingChessPiece.IsWhitePiece ? WhiteChessPieces : BlackChessPieces;
        int rmChessPieceIndex = curChessPieces.FindIndex(piece => ReferenceEquals(piece, removingChessPiece));
        if (rmChessPieceIndex == -1)
            throw new ChessRuleException("The piece is not on the chessboard.");

        int index = removingChessPiece.IndexInChessboard;
        for (int i = rmChessPieceIndex + 1; i < curChessPieces.Count; ++i)
        {
            BaseChessPiece piece = curChessPieces[i];
            _charChessboard[index] = piece.CharChessPiece;
            piece.IndexInChessboard = index;
            index += removingChessPiece.IsWhitePiece ? 1 : -1;
        }
        _charChessboard[index] = ' ';
        curChessPieces.RemoveAt(rmChessPieceIndex);
        ref int curChessPiecesValue = ref (removingChessPiece.IsWhitePiece ? ref _whiteChessPiecesValue : ref _blackChessPiecesValue);
        curChessPiecesValue -= removingChessPiece.ChessPieceValue;
        removingChessPiece.IndexInChessboard = -1;
    }
    public void Update()
    {
        PrintChessboard();
    }
    public override string ToString() => $"This chessboard's edge length = {_edgeLength}";
    private void PrintChessboard()
    {
        Console.WriteLine(Parts.TOP_LEFT_CORNER + new string(Parts.HORIZONTAL_BORDER, _edgeLength)  + Parts.TOP_RIGHT_CORNER);

        for (int i = 0; i < _edgeLength; ++i)
        {
            Console.Write(Parts.VERTICAL_BORDER);
            Console.Write(_charChessboard.GetRange(i * _edgeLength, _edgeLength).ToArray());
            Console.WriteLine(Parts.VERTICAL_BORDER);
        }

        Console.WriteLine(Parts.BOTTOM_LEFT_CORNER + new string(Parts.HORIZONTAL_BORDER, _edgeLength) + Parts.BOTTOM_RIGHT_CORNER);
    }
};