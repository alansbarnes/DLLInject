#pragma once

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include <memory>
#include <mutex>
#include "trace.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#ifdef UDPCLIENT_EXPORTS  
#define UDPCLIENT_API __declspec(dllexport)   
#else  
#define UDPCLIENT_API __declspec(dllimport)   
#endif  

class UDPClient
{

public:
    UDPClient();
    ~UDPClient();
    UDPCLIENT_API unsigned long gethost();
    UDPCLIENT_API string getPort() { return m_strPort; }
    UDPCLIENT_API string getServerIP() { return string(m_szServerIP); }
    SOCKET getServerSocket() { return m_serverSocket; }
    void setServerSocket(SOCKET socket) { m_serverSocket = socket; }
    static shared_ptr<UDPClient>& getClient() { return m_client; }
    static void setClient(shared_ptr<UDPClient>& client) { m_client = client; }
    static int sendUDPDatagram(const string c_strMsg);
    static UDPCLIENT_API shared_ptr<UDPClient> CreateInstance();

private:
    char m_szServerIP[16];
    SOCKET m_serverSocket;
    string m_strPort;
    bool m_bWSAStarted;
    static shared_ptr<UDPClient> m_client;
    static mutex lock;
};