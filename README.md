# Лабораторная работа 5. Полиморфизм

Тема проекта: игра «Шахматы 2.0».

Ретивых Михаил Сергеевич, группа ПИ-51.

Общая основа для ЛР5 объединяет реализации ЛР4 из `retivykh's-labs/lab-04-cpp` и `retivykh's-labs/lab-04-csharp`.

## C++

Сборка и запуск из корня репозитория (Windows, g++ с поддержкой C++20):

```powershell
cd console/scripts
g++ -std=c++20 main.cpp GameManagement.cpp Chessboard.cpp BaseChessPiece.cpp Pawn.cpp Rook.cpp ShortPieceFormatter.cpp DetailedPieceFormatter.cpp -o app.exe
.\app.exe
```

## C#

Сборка и запуск из корня репозитория (Windows, .NET SDK 10):

```powershell
dotnet build "lab work on c#/ChessApp.csproj" -c Release
dotnet run --project "lab work on c#/ChessApp.csproj" -c Release --no-build --no-restore
```

C++ демонстрирует интерфейс IDescribable, раннее и позднее связывание, dynamic_cast и смену IPieceFormatter в GameManagement. Форматтер возвращает строку, GameManagement выводит её в консоль.

Обе реализации содержат иерархию `BaseChessPiece` → `Pawn`, `Rook` и демонстрации копирования из ЛР4.
