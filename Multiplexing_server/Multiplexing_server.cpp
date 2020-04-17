#include <iostream>
#include <WinSock2.h>

#define PORT 1234

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKADDR_IN servAddr;


	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	SOCKET servSock;
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		std::cout << "socket err";
		WSACleanup();
		return 1;
	}
	

	if (bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == INVALID_SOCKET) {
		std::cout << "bind err";
		WSACleanup();
		return 1;
	}

	if (listen(servSock, SOMAXCONN) == SOCKET_ERROR) {
		std::cout << "listen err";
		WSACleanup();
		return 1;
	}

	fd_set read; // 원래의 fd_set
	fd_set cpyRead; // 변화된 fd_set을 위함
	int iRet;
	unsigned int i;
	SOCKET socktmp, sockClnt;
	SOCKADDR_IN addrClnt;
	int addrSize;
	char recvBuff[255];
	int recvSize;

	FD_ZERO(&read);
	FD_SET(servSock, &read);

	while (1) {
		cpyRead = read;
		iRet = select(0, &cpyRead, 0, 0, 0);
		if (iRet == SOCKET_ERROR) break;

		for (i = 0; i < read.fd_count; ++i) {
			socktmp = read.fd_array[i];
			if (FD_ISSET(socktmp, &cpyRead)) {
				if (socktmp == servSock) {
					addrSize = sizeof(addrClnt);
					sockClnt = accept(servSock, (SOCKADDR*)&addrClnt, &addrSize);
					FD_SET(sockClnt, &read);
					std::cout << i+1 << " client connected" << addrClnt.sin_addr.S_un.S_un_b.s_b1 << ", " <<
						addrClnt.sin_addr.S_un.S_un_b.s_b2 << ", " <<
						addrClnt.sin_addr.S_un.S_un_b.s_b3 << ", " <<
						addrClnt.sin_addr.S_un.S_un_b.s_b4;
				}
				else {
					recvSize = recv(socktmp, recvBuff, sizeof(recvBuff), 0);
					if (recvSize > 0) {
						send(socktmp, recvBuff, recvSize, 0);
					}
					else {
						FD_CLR(socktmp,&read);
						closesocket(socktmp);
						std::cout << "close socket" << socktmp <<"\n";
					}
				}
			}

		}

	}




	closesocket(servSock);
	WSACleanup();
	return 0;
}

