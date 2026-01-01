#include "ForegroundWnd.h"

ForegroundWnd::ForegroundWnd(HWND hwnd, string strWndClass) : m_hwnd(hwnd), m_hinstDLL(NULL), m_hHook1(NULL), m_hHook2(NULL), m_strWndClass(strWndClass)
{
    trace("+ForegroundWnd::ForegroundWnd (\"%s\", hwnd = 0x%p)\n", m_strWndClass.c_str(), m_hwnd);
    InstallHook(m_strWndClass.c_str());
}

ForegroundWnd::~ForegroundWnd()
{
    trace("+ForegroundWnd::~ForegroundWnd (\"%s\", hwnd = 0x%p)\n", m_strWndClass.c_str(), m_hwnd);
    UninstallHook();
}

void ForegroundWnd::InstallHook(const char *szWnd)
{
    trace("+%s\n", __FUNCTION__);
    HOOKPROC hkprc;
    
    if (string(szWnd) == string("Notepad"))
    {
        m_hinstDLL = LoadLibrary(TEXT("UDPClient.dll"));

        if (m_hinstDLL)
        {
            hkprc = (HOOKPROC)GetProcAddress(m_hinstDLL, "GetMsgProc");
            m_hHook1 = SetWindowsHookEx(WH_GETMESSAGE, hkprc, m_hinstDLL, 0);
            hkprc = (HOOKPROC)GetProcAddress(m_hinstDLL, "CallWndProc");
            m_hHook2 = SetWindowsHookEx(WH_CALLWNDPROC, hkprc, m_hinstDLL, 0);
        }
    }
    else if (_stricmp(szWnd, "Save As") == 0)
    {
        m_hinstDLL = LoadLibrary(TEXT("UDPClient.dll"));

        if (m_hinstDLL)
        {
            hkprc = (HOOKPROC)GetProcAddress(m_hinstDLL, "CallWndProc");
            m_hHook1 = SetWindowsHookEx(WH_CALLWNDPROC, hkprc, m_hinstDLL, 0);
        }
    }
}

void ForegroundWnd::UninstallHook()
{
    trace("+%s\n", __FUNCTION__);

    if (m_hHook2)
    {
        trace("%s: UnhookWindowsHookEx(m_hHook2)\n", __FUNCTION__);
        UnhookWindowsHookEx(m_hHook2);
        m_hHook2 = NULL;
    }

    if (m_hHook1)
    {
        trace("%s: UnhookWindowsHookEx(m_hHook1)\n", __FUNCTION__);
        UnhookWindowsHookEx(m_hHook1);
        m_hHook1 = NULL;
    }

    if (m_hinstDLL)
    {
        FreeLibrary(m_hinstDLL);
        m_hinstDLL = NULL;
    }
}

shared_ptr<ForegroundWnd> ForegroundWnd::m_spNotepadWnd;
shared_ptr<ForegroundWnd> ForegroundWnd::m_spSaveAsWnd;
