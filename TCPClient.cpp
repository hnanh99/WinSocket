// g++ TCPclient.cpp -o TCPclient.exe -lws2_32

#include <Winsock2.h>
#include <string.h>
//#pragma comment(lib,"Ws2_32.lib")

#include <iostream>
using namespace std;

int main()
{
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

    unsigned long conv_addr;
    conv_addr = inet_addr(cp);
    cout << "By inet_addr: " << conv_addr << endl; 

    const char*instr = cp;
    int check;
    const char*addr_out;
    if (check = InetPtonW(AF_INET, instr, &addr_out)==-1)
    {
        cout << "Error";
    }
    else if (check == 0)
    {
        cout << "Xâu không hợp lệ";
    }
    else 
    {
        cout << "By inet_pton: "<< addr_out << endl;
    }

    if((WSACleanup())==SOCKET_ERROR)    
    {
        cout << "WSACleanup failed with error" << WSAGetLastError() << endl;
    }

    return 0;
}