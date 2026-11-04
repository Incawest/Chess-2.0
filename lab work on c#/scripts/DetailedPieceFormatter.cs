public sealed class DetailedPieceFormatter : IPieceFormatter
{
    public string Format(BaseChessPiece piece) =>
        $"{piece.Name}: symbol = {piece.CharChessPiece}, value = {piece.ChessPieceValue}, is white = {piece.IsWhitePiece}, index = {piece.IndexInChessboard}";
}
