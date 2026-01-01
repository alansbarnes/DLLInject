#pragma once

#include <windows.h>
#include <string>
#include <memory>
#include "Trace.h"

using namespace std;

class ForegroundWnd
{
public:
    ForegroundWnd(HWND hwnd, string strWndClass);
    ~ForegroundWnd();
    HWND getHwnd() { return m_hwnd; }
    string getWndClass() { return m_strWndClass; }
    void InstallHook(const char *szWnd);
    void UninstallHook();
    static shared_ptr<ForegroundWnd> m_spNotepadWnd;
    static shared_ptr<ForegroundWnd> m_spSaveAsWnd;

private:
    HWND m_hwnd;
    HINSTANCE m_hinstDLL;
    HHOOK m_hHook1;
    HHOOK m_hHook2;
    HOOKPROC m_hkprc;
    string m_strWndClass;
};
