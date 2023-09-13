// BT2: Tiến trình Server
// - Khởi tạo socket cho Server
// - Hàm Bind
// - Hàm listen


// g++ filename.cpp -o filename.exe -lws2_32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include <Winsock2.h>
#include <string.h>
#include <iostream>

#include "Setting.h"

//#pragma comment(lib,"Ws2_32.lib")

using namespace std;

int main()
{
    //startup
    WORD wVersion = MAKEWORD(2,2);
    WSADATA wsaDATA;

    int Startup;
    if((Startup=WSAStartup(wVersion, &wsaDATA))!=0)
    {
        cout << "Startup unsuccessful\n";
    }

    const char*cp = "127.0.0.148";

    //Step1: Create a socket
    SOCKET listensock;
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (listensock == INVALID_SOCKET)
    {
        cout << "Creating socket failed with code " << WSAGetLastError() <<endl;
    }
    else
    {
        cout << "Creating socket completed successfully " << listensock << endl;
    }

    //Step2: Bind
    sockaddr_in tcpServerAddr;
    tcpServerAddr.sin_family = AF_INET;
    tcpServerAddr.sin_port = htons(SERVER_PORT);
    tcpServerAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);

    if(!bind(listensock,(sockaddr *) &tcpServerAddr, sizeof(tcpServerAddr)))
    {
        cout << "Bind API completed successfully" << endl;
    }
    else 
    {
        cout << "Bind API failed with code " << WSAGetLastError() << endl;
    }

    //Step 3: Listening
    int backlog = 5;
    if(!listen(listensock,backlog))
    {
        cout << "Successfully !!! Server is listening" << endl;
    }
    else
    {
        cout << "Listen failed with code " << WSAGetLastError() << endl;
    }

    closesocket(listensock);


    // Cleanup
    if((WSACleanup())==SOCKET_ERROR)    
    {
        cout << "WSACleanup failed with error" << WSAGetLastError() << endl;
    }

    return 0;
}