//g++ UDPClient.cpp -o UDPCient.exe -lws2_32

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include <Winsock2.h>
#include <string.h>
#include <iostream>

#include "Setting.h"

using namespace std;

int main(int argc,char** argv){
    
    if (argc != 4){
        cout << "Wrong arguemnt: UDPClient.exe <server_IP> <port_number> <domain_name>";
        return 0;
    };
    char *server_IP = argv[1];
    cout << "server_IP: " << server_IP << endl;
    int port_number = atoi(argv[2]);
    cout << "port_number: " << port_number << endl;
    char *domain_name = argv[3];
    cout << "domain_name: " << domain_name << endl;
        

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

    //Step2: Sendto
    sockaddr_in udpServerAddr;
    udpServerAddr.sin_family = AF_INET;
    udpServerAddr.sin_port = htons(port_number);
    udpServerAddr.sin_addr.S_un.S_addr = inet_addr(server_IP);

    if((result = sendto(sock,domain_name,(int)strlen(domain_name),0,(sockaddr*)&udpServerAddr,sizeof(udpServerAddr))) == SOCKET_ERROR){
        cout << "send error with code " << WSAGetLastError() << endl;
    }
    else{
        cout << "Sended " << result << " bytes" << endl;
    };

    closesocket(sock);

    WSACleanup();
    return 0;
}