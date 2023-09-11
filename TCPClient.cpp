// BT1: CHUYỂN ĐỔI ĐỊA CHỈ IP
// Viết 1 đoạn chương trình chuyển đổi địa chỉ IP:
// 1. Dùng hàm inet_addr với tham số đầu vào : cp : “127.0.0.x”, với x = ([mã SV] modulo 255) + 1
// 2. Dùng hàm inet_pton với tham số đầu vào :
//    family : AF_INET
//    ipstr : “127.0.0.x”, với x = ([mã SV] modulo 255) + 1
// Xuất ra giá trị số (kiểu unsigned long) biểu diễn địa chị IP dạng nhị phân cho 2 cách trên

// Huỳnh Nhật Ánh - 106200252 - 20KTMT2
// x = (106200252 % 255) + 1 = 148


// g++ TCPclient.cpp -o TCPclient.exe -lws2_32
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

    closesocket(listensock);


    // Cleanup
    if((WSACleanup())==SOCKET_ERROR)    
    {
        cout << "WSACleanup failed with error" << WSAGetLastError() << endl;
    }

    return 0;
}