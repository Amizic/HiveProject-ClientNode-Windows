#include <iostream>
#include <stdio.h>

#include "EnvironmentOptions.h"
#include "ASCIIART.h"
#include "ColorCodes.h"

#include "HiveClientNode.h"



int main()
{
    WSADATA wsaData;
    DWORD lastError;


    //Handle for console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int error;
    //int serverConnectionTimeout = -1;
    //int readValue;

    //Request for WSA 2.2 version
    error = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (error != 0) {
        SetConsoleTextAttribute(hConsole, _RED);
        cerr << "WSAStartup failed with error: " << error << "\n";
        return 1;
    }
    SetConsoleTextAttribute(hConsole, _GREEN);
    cout << "WSA started..." << endl;


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Couldnt find usable WinSock DLL */
        SetConsoleTextAttribute(hConsole, _RED);
        cerr << "Could not find version of Winsock.dll that can be used" << "\n";
        WSACleanup();
        return -1;
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTextAttribute(hConsole, _CYAN);



    SetConsoleTextAttribute(hConsole, _WHITE);



    SetConsoleTextAttribute(hConsole, _CYAN);
    GreetingsAngel();
    HiveClientNode hiveClientNodeObject;
    cout << "Defining server properties...\n";
    hiveClientNodeObject.DefineServerIPV4(_SERVER_PORT);

    cout << "Creating client socket for data transfer...\n";

    if (hiveClientNodeObject.CreateClientSocket() < 0) {
        lastError = GetLastError();
        SetConsoleTextAttribute(hConsole, _RED);
        cout << "Error:" << lastError << "\n" << "Unable to create client socket...\n";
     }


    SetConsoleTextAttribute(hConsole, _GREEN);
    cout << "Client socket created!\n";

    SetConsoleTextAttribute(hConsole, _WHITE);
    cout << "---CLIENT_APPLICATION---\n\n";
    cout << "File Descriptors:\n\n";

    cout << "\t1.FD:" << hiveClientNodeObject.GetClientSocket();
    cout << "\n\t  Description: Client socket used to communicate with server.\n\n";

        //recv(hiveClientNodeObject.GetClientSocket(), (char*)hiveClientNodeObject.message, 1024, 0);


    SetConsoleTextAttribute(hConsole, _RED);
    while (hiveClientNodeObject.ConnectToServer() != 0) {
        cout << "Connection to server node could not be established...\n";

    }

    SetConsoleTextAttribute(hConsole, _GREEN);
    cout << "\nConnection to server established successfully!\n";
    SetConsoleTextAttribute(hConsole, _WHITE);
    while(1){
       hiveClientNodeObject.ReadDataFromServer();
     }


    
}