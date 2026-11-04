public sealed class ShortPieceFormatter : IPieceFormatter
{
    public string Format(BaseChessPiece piece) => $"{piece.Name} ({piece.CharChessPiece})";
}
