
// g++ TCPServer.cpp -o TCPServer.exe -lws2_32
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
    else 
    {cout << "Startup successful\n";};

    const char*cp = "127.0.0.148";

    //inet_addr
    unsigned long conv_addr;
    conv_addr = inet_addr(cp);
    cout << "By inet_addr: " << conv_addr << endl; 

    //inet_pton
    int check;
    sockaddr_in addr_out;
    if ((check = inet_pton(AF_INET, cp, &addr_out.sin_addr)) < 1)
    {
        cout << "Error Inet Pton:" << GetLastError() << endl;
    }
    else if (check == 1)
    {
        cout << "By inet_pton: " << addr_out.sin_addr.S_un.S_addr << endl; //s_union . s_address?
    }

    //Step1: Create a socket
    SOCKET listensock;
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (listensock == INVALID_SOCKET)
    {
        cout << "Socket function error: " << WSAGetLastError() <<endl;
    }
    else
    {
        cout << "Create socket complete: " << listensock << endl;
    }

    //Step2: Bind
    sockaddr_in tcpServerAddr;
    tcpServerAddr.sin_family = AF_INET;
    tcpServerAddr.sin_port = htons(SERVER_PORT);
    tcpServerAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);

    if(!bind(listensock,(sockaddr *) &tcpServerAddr, sizeof(tcpServerAddr)))
    {
        cout << "Bind API completed seccessfully" << endl;
        //return 0;
    }

    //Step 3: Listening
    int backlog = 5;
    if(!listen(listensock,backlog))
    {
        cout << "Successfully !!! Server is listening" << endl;
    }

    //Step 4: Accept
    SOCKET accept_socket;

    if ((accept_socket = accept(listensock,NULL,NULL))==INVALID_SOCKET)
    {
        cout << "Accept failed with error: " << WSAGetLastError();

    }
    else
    {
        cout << "Client connected" << endl;
    };
    
    //Step 5: Receive
    int result;
    char *recvbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    if((result = recv(accept_socket,recvbuf,recvbuflen,0)) == SOCKET_ERROR){
        cout << "Recv failed: %d\n" << WSAGetLastError();
        
    }
    else if ( result == 0 ){
        cout << "Connection closed\n";
    }
    else{
        cout << "Bytes received:" <<  result << endl;
        cout << recvbuf << endl;
    };
    
    //Step 6: Send
    char const *sendbuf = "Message from server: received";
    if ((result = send(accept_socket, sendbuf, (int)strlen(sendbuf),0)) == SOCKET_ERROR){
        cout << "Send failed with code: " << WSAGetLastError() << endl;
    }
    else{
        cout << "Send " << result << "bytes" << endl;
    }

    shutdown(accept_socket, 2);
    closesocket(listensock);


    // Cleanup
    if((WSACleanup())==SOCKET_ERROR)    
    {
        cout << "WSACleanup failed with error" << WSAGetLastError() << endl;
    }

    return 0;
}