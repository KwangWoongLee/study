#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT 1234
#define PACKET_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET hSocket;
    hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (hSocket == INVALID_SOCKET)
    {
        std::cout << "잘못된 소켓";
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN tAddr;
    memset(&tAddr, 0, sizeof(tAddr));
    tAddr.sin_family = AF_INET;
    tAddr.sin_port = htons(PORT);
    tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr)) == SOCKET_ERROR) {
        std::cout << "connect 에러";
        WSACleanup();
        return 1;
    }

    char cBuffer[] = "클라이언트가 보낸 메세지";
    send(hSocket, cBuffer, strlen(cBuffer), 0);

    char rBuffer[PACKET_SIZE] = {};
    recv(hSocket, rBuffer, PACKET_SIZE, 0);

    std::cout << rBuffer;

    closesocket(hSocket);

    WSACleanup();
    return 0;
}