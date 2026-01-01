#include "ThreadMap.h"

void ThreadMap::insert(char drive)
{
    threads[drive - 'a'].bRunning = true;
}

void ThreadMap::remove(char drive)
{
    threads[drive - 'a'].bRunning = false;
}

bool ThreadMap::running(char drive)
{
    return threads[drive - 'a'].bRunning;
}

array<ThreadMap::THREAD_DATA, 'z' - 'a' + 1> ThreadMap::threads;
string ThreadMap::strFile;
bool ThreadMap::bDone = false;
bool ThreadMap::bExit = false;
mutex ThreadMap::lock;
