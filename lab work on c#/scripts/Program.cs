Console.OutputEncoding = System.Text.Encoding.UTF8;

void PrintDescription(IDescribable obj)
{
    Console.WriteLine(obj.Describe());
}

using IssueLog log = new IssueLog("LOG");
BaseChessPiece[] pieces = {new Pawn(), new Rook(false)};

Console.WriteLine("-------BINDING-------");
Console.WriteLine($"Early: {pieces[0].GetClassName()}");
Console.WriteLine($"Late: {pieces[0].Describe()}");

Console.WriteLine("-------INTERFACE-------");
foreach (BaseChessPiece piece in pieces)
{
    if (piece is IDescribable describable)
        PrintDescription(describable);
}
Pawn? pawn = pieces[0] as Pawn;
if (pawn is not null)
    Console.WriteLine($"Derived: {pawn.GetClassName()}");
Console.WriteLine($"Rook is Pawn = {pieces[1] is Pawn}");

GameManagement gameManagement = new GameManagement(8, 5);
foreach (BaseChessPiece piece in pieces)
    gameManagement.MainChessboard.AddChessPiece(piece);

Console.WriteLine("-------FORMATTER-------");
gameManagement.SetPieceFormatter(new ShortPieceFormatter());
Console.Write("Short: ");
gameManagement.PrintPieceInfo(pieces[0]);
gameManagement.SetPieceFormatter(new DetailedPieceFormatter());
Console.Write("Detailed: ");
gameManagement.PrintPieceInfo(pieces[0]);

Console.WriteLine("-------COMPARABLE-------");
BaseChessPiece[] sortedPieces = {pieces[1], pieces[0]};
Array.Sort(sortedPieces);
Console.WriteLine("Sorted: " + string.Join(", ", sortedPieces.Select(piece => piece.Name)));

gameManagement.MainChessboard.Update();
log.Write("Program end");
