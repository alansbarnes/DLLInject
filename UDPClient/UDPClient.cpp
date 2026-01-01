#ifndef UDPCLIENT_EXPORTS
#define UDPCLIENT_EXPORTS
#endif

#include "UDPClient.h"

UDPClient::UDPClient() : m_serverSocket(INVALID_SOCKET)
{
    WSADATA wsaData;
    m_strPort = "12345";
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (iResult != 0)
    {
        trace("WSAStartup failed with error: %d\n", iResult);
        m_bWSAStarted = false;
    }
    else
    {
        m_bWSAStarted = true;
    }
}

UDPClient::~UDPClient()
{
    if (m_bWSAStarted)
    {
        WSACleanup();
    }
}

UDPCLIENT_API unsigned long UDPClient::gethost()
{
    char szHostName[257];
    gethostname(szHostName, sizeof(szHostName));

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    int iResult = getaddrinfo(szHostName, m_strPort.c_str(), &hints, &result);
    
    if (iResult != 0)
    {
        trace("getaddrinfo failed with error: %d\n", iResult);
        return 1;
    }

    sockaddr_in *sin = (sockaddr_in *)result->ai_addr;
    inet_ntop(AF_INET, &sin->sin_addr, m_szServerIP, _countof(m_szServerIP));
    return 0;
}

int UDPClient::sendUDPDatagram(const string c_strMsg)
{
    lock_guard<mutex> lg(UDPClient::lock);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(getClient().get()->getPort().c_str()));
    inet_pton(AF_INET, getClient().get()->getServerIP().c_str(), &server_addr.sin_addr.s_addr);
    return sendto(getClient()->getServerSocket(), c_strMsg.c_str(), (int)c_strMsg.length(), 0, (sockaddr *)&server_addr, sizeof(server_addr));
}

UDPCLIENT_API shared_ptr<UDPClient> UDPClient::CreateInstance()
{
    return make_shared<UDPClient>();
}

shared_ptr<UDPClient> UDPClient::m_client;
mutex UDPClient::lock;
