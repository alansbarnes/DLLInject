#include "Watchdog.h"

void PollingThread(bool *pbExiting, HWND hwnd)
{
    while (!*pbExiting)
    {
        // PeekMessage
        Sleep(100);
    }
}

Watchdog::Watchdog(HWND hwnd) : m_bExiting(false)
{
    sp_t = make_unique<thread>(PollingThread, &m_bExiting, hwnd);
    sp_t->detach();
}

Watchdog::~Watchdog()
{
    m_bExiting = true;
}
