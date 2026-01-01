#pragma once
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <windows.h>
#include <functional>
#include <thread>
#include <memory>

using namespace std;

class Watchdog
{
public:
    Watchdog(HWND hwnd);
    ~Watchdog();
    void ExitWatchdog()
    {
        m_bExiting = true;
    }
private:
    unique_ptr<thread> sp_t;
    bool m_bExiting;
};

#endif
