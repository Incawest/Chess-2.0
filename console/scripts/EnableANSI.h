#pragma once

#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <cstdio>

inline bool EnableConsoleUnicodeAndANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE || hOut == nullptr)
        return false;

    DWORD outputMode = 0;

    if (!GetConsoleMode(hOut, &outputMode))
        return false;

    outputMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if (!SetConsoleMode(hOut, outputMode))
        return false;

    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1)
        return false;

    if (_setmode(_fileno(stdin), _O_U16TEXT) == -1)
        return false;

    return true;
}