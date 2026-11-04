# Лабораторная работа 5. Полиморфизм

Тема проекта: игра «Шахматы 2.0».
Ретивых Михаил Сергеевич, группа ПИ-51.

Ветка C++ объединяет обе реализации ЛР4. Ветка C# создана от завершённой ветки C++ ЛР5.

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

`Pawn` и `Rook` наследуются от `BaseChessPiece` и реализуют `IDescribable`.
`PrintDescription` работает через интерфейс; `GetClassName` и `Describe` показывают раннее и позднее связывание.
Проверка типов показана через `dynamic_cast` в C++ и `is` / `as` в C#.

`GameManagement` хранит `IPieceFormatter` и динамически переключает краткое и подробное форматирование.
Форматтер возвращает строку, `GameManagement` выводит её в консоль.
В C# `IComparable` позволяет сортировать фигуры по имени, а `using IssueLog` закрывает журнал при любом выходе из области видимости.

`ChessRuleException` сообщает о превышении ценности набора, отсутствии свободной клетки, повторном добавлении и удалении отсутствующей фигуры.
При отказе состав, позиции и суммарная ценность набора не изменяются.
В выводе есть успешное добавление, перехваченные нарушения правил и два формата одной фигуры.
Иерархия и копирование объектов сохранены из ЛР4.
