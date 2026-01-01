#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <array>
#include <memory>
#include <thread>
#include <mutex>

using namespace std;

class ThreadMap
{
public:
    static void insert(char drive);
    static void remove(char drive);
    static bool running(char drive);
    static mutex lock;

    typedef struct
    {
        shared_ptr<thread> t;
        HANDLE hEvent;
        bool bRunning;
    } THREAD_DATA;

    static array<THREAD_DATA, 'z' - 'a' + 1> threads;
    static string strFile;
    static bool bDone;
    static bool bExit;
};