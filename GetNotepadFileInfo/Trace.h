#pragma once

#include <stdio.h>

#define trace(format, ...)                                              \
{                                                                       \
    char message[MAX_PATH];                                             \
    sprintf_s(message, _countof(message), format, __VA_ARGS__);         \
    OutputDebugStringA(message);                                        \
}
