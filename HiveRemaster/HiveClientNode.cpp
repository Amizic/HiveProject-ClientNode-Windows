#include "HiveClientNode.h"

HiveClientNode::HiveClientNode()
{
    //ctor
}


HiveClientNode::~HiveClientNode()
{
    //dtor
}

SOCKET HiveClientNode::GetClientSocket() {
    return this->clientSocket;
}

//Create socket for client for IPV4 protocol
SOCKET HiveClientNode::CreateClientSocket() {
    return this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
}

//Closing of socket
int HiveClientNode::CloseClientSocket() {
    if (closesocket(this->clientSocket) == SOCKET_ERROR) {
        return -1;
    }
    return 1;
}

//Define server address
void HiveClientNode::DefineServerIPV4(int port) {
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(port);
    //this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    //this->serverAddress.sin_addr.s_addr = '127.0.0.1';

    //If you work over internet, make sure that server side is binded to your actual local address, and not loop!
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
}


//Connect to server
int HiveClientNode::ConnectToServer() {
    return connect(this->clientSocket, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress));
}

//Send data to server from Client
int HiveClientNode::SendDataToServer(const char* Data) {
    //const char* message = "TEST DATA TRANSMISSION FROM CLIENT";
    //std::cout << message <<std::endl;
    return send(this->clientSocket, Data, strlen(Data), 0);
}


//Reading of data from server
void HiveClientNode::ReadDataFromServer() {
    char buffer[1024] = { 0 };
    recv(this->clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from server: " << buffer << std::endl;
}
