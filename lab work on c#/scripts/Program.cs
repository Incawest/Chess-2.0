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
Console.WriteLine("-------RULES-------");
try
{
    foreach (BaseChessPiece piece in pieces)
        gameManagement.MainChessboard.AddChessPiece(piece);
    Console.WriteLine("Added Pawn and Rook");
}
catch (ChessRuleException error)
{
    Console.WriteLine("Rule: " + error.Message);
}
Rook extraRook = new Rook();
try
{
    gameManagement.MainChessboard.AddChessPiece(extraRook);
}
catch (ChessRuleException error)
{
    Console.WriteLine("Rule: " + error.Message);
}
try
{
    gameManagement.MainChessboard.RemoveChessPiece(extraRook);
}
catch (ChessRuleException error)
{
    Console.WriteLine("Rule: " + error.Message);
}
Console.WriteLine($"White pieces after refusal = {gameManagement.MainChessboard.WhiteChessPieces.Count}");

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
