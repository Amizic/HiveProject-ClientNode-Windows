#ifndef HIVECLIENTNODE_H
#define HIVECLIENTNODE_H

#include "EnvironmentOptions.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>



#include "IHiveClientNode.h"
/*
    ####MANUAL####
    1. Create client socket
    2. Define server address
    3. Connect to server
    4. Send/Receive data from server
    5. Close client socket

*/

class HiveClientNode : public IHiveClientNode
{
private:

    SOCKET clientSocket;
    sockaddr_in serverAddress;

public:
    char message[1024];
    HiveClientNode();
    virtual ~HiveClientNode();

    SOCKET CreateClientSocket() override;
    int CloseClientSocket() override;
    SOCKET GetClientSocket() override;
    void DefineServerIPV4(int port) override;
    int ConnectToServer() override;
    int SendDataToServer(const char* Data) override;
    void ReadDataFromServer() override;

};

#endif // HIVECLIENTNODE_H