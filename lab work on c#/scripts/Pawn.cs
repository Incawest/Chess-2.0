public sealed class Pawn : BaseChessPiece, IDescribable
{
    public Pawn() : base('P', 1, true, "Pawn")
    {
        Console.WriteLine("Pawn was created (default)");
    }

    public Pawn(bool isWhitePiece) : base('P', 1, isWhitePiece, "Pawn")
    {
        Console.WriteLine("Pawn was created (parameters)");
    }

    public Pawn(Pawn other) : base(other)
    {
        Console.WriteLine("Pawn was copied");
    }

    public new string GetClassName() => "Pawn";

    public override string Describe() => base.Describe() + $", symbol = {_charChessPiece}";

    public override BaseChessPiece Clone() => new Pawn(this);
}
