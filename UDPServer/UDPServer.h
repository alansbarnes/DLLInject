#pragma once

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>
#include "trace.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class UDPServer
{
public:
    UDPServer();
    ~UDPServer();
    SOCKET getSocket() { return m_serverSocket; }
    const string logfile{ ".\\FileLog.txt" };

private:
    SOCKET m_serverSocket;
    string m_strPort;
    bool m_bWSAStarted;
};