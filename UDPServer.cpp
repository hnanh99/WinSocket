//g++ UDPServer.cpp -o UDPServer.exe -lws2_32

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include <Winsock2.h>
#include <string.h>
#include <iostream>

#include "Setting.h"

using namespace std;

int main(int argc, char**argv){
    
    if (argc != 2){
        cout << "Wrong arguemnt: UDPServer.exe <port_number>";
        return 0;
    };
    int port_number = atoi(argv[1]);
    cout << "port_number: " << port_number << endl;

    WORD wVersion = MAKEWORD(2,2);
    WSADATA wsaDATA;

    int Startup;
    int result;
    if((Startup=WSAStartup(wVersion, &wsaDATA))!=0)
    {
        cout << "Startup unsuccessful\n";
    }
    else 
    {cout << "Startup successful\n";};

    //const char*cp = "127.0.0.148";

    //Step1: Create a socket
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (sock == INVALID_SOCKET)
    {
        cout << "Socket function error: " << WSAGetLastError() <<endl;
    }
    else
    {
        cout << "Create socket complete: " << sock << endl;
    }

    //Step2: Bind
    sockaddr_in udpServerAddr;
    udpServerAddr.sin_family = AF_INET;
    udpServerAddr.sin_port = htons(port_number);
    //udpServerAddr.sin_addr.S_un.S_addr = inet_addr(INADDR_ANY);
    udpServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    if(!bind(sock,(sockaddr *) &udpServerAddr, sizeof(udpServerAddr)))
    {
        cout << "Bind API completed seccessfully" << endl;
        //return 0;
    }
    else {
        cout << "Bind error with code " << WSAGetLastError() <<endl;
    }

    //Step3: recvfrom
    char recvbuf[DEFAULT_BUFLEN];
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    cout << "Start receive" << endl;
    if ((result = recvfrom(sock,recvbuf,DEFAULT_BUFLEN,0,(sockaddr *)&clientAddr, &clientAddrLen)) == SOCKET_ERROR){
        cout << "recvfrom error with code " << WSAGetLastError() << endl;
    }
    else{
        cout << "Received " << result << "bytes" << endl;
        cout << "Message: " << recvbuf << endl;
    };

    closesocket(sock);
    
    WSACleanup();

    return 0;
}