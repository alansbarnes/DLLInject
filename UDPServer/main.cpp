#include "UDPServer.h"

int main()
{
    UDPServer server;
    int received = 0;

    do
    {
        ofstream f(server.logfile, ios_base::app);
        char buf[4096] = { 0 };
        received = recvfrom(server.getSocket(), buf, sizeof(buf), 0, nullptr, nullptr);
        
        if (received)
        {
            cout << buf;
            f << buf;
        }
    } while (received > 0);

    return 0;
}
