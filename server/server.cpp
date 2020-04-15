//소켓프로그래밍 서버입니다.
//설정 : 윈도우 환경에서 소켓을 사용하려면 Winsock2.h 헤더파일이 필요합니다.
//      이를 위해, 비쥬얼 스튜디오에서 ws2_32.lib를 추가해야 합니다.
//방법 : (1)프로젝트 - 속성 - 구성속성 - 링커 - 추가종속성 - ws2_32.lib 추가 
//       (2)프로젝트 - 속성 - 구성속성 - 매니페스트 도구 - 입력 및 출력 - 매니페스트 포함 - 아니요 설정

//1. 포트를 bind 합니다.
//2. bind한 포트에 listen을 통해 클라이언트의 접속을 기다립니다.
//3. 클라이언트가 접속하지 않는다면 계속 블로킹합니다.
//4. 클라이언트 측에서 connect를 통해 접근합니다.
//5. 서버 측에서 accept를 통해 접근을 허용합니다.
//6. 서버와 클라이언트 간 read write를 통해 주고받습니다.
//7. 연결이 종료되면 close를 통해 소켓을 종료합니다.

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>   //소켓 사용을 위한 헤더파일 

#define PORT 1234   //서버의 소켓 포트 지정 , 포트는 지정포트를 제외하고 즉, 1000번아래와 8080(http포트) 등은 제외  
#define PACKET_SIZE 1024 //패킷 사이즈 지정


int main()
{
	WSADATA wsaData; // 윈도우의 소켓 초기화 정보를 저장하기 위한 구조체.
	WSAStartup(MAKEWORD(2, 2), &wsaData); // 윈도우에서 사용할 소켓을 지정한다. 윈속을 초기화한다. 최초한번만 하는 과정들
	// MAKEWORD 는 함수가 아니라 매크로로서 WORD를 리턴한다 . 그냥 2.2버전이라고 생각하면된다. 2.0버전은 MAKEWORD(2,0)하면된다.
	// 두번째 인자는 윈속 구조체의 포인터이다.
	//WSAStartup과 WSACleanup 사이에 소켓활용을 한다.



	// 서버는 소켓을 두가지 사용해야한다.
	// 첫번째 소켓은, 들어오는 요청에 대하여 접속승인(accept) 하는 소켓이다.
	// 두번째 소켓은, 들어온 클라이언트에 연결된 소켓이다.


	SOCKET hListen; // 들어오는 요청에 대하여 접속 승인하는 소켓변수 생성. 소켓은 핸들(운영체제의 커널에서 관리하는 커널오브젝트의 한 종류)이다. 
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // socket은 함수가 아니라 system call이다.
	//system call이란, 커널영역의 기능을 사용자 모드가 사용 가능하게,즉, 프로세스가 하드웨어에 직접 접근하여 필요한 기능을 사용할 수 있게해준다.
	// 첫번째 인자로는 domain 즉, 프로토콜 패밀리가 들어간다. 어떤 영역에서 통신할 것인가를 정한다. PF_INET은 IPv4를 PF_INET6는 IPv6를.
	// 두번째 인자로는 프로토콜 타입을 넘긴다. 사용자정의(SOCK_RAW), TCP(SOCK_STREAM), UDP(SOCK_DGRAM) 세가지의 종류가 있다.
	// 세번째 인자로는 사용할 프로토콜을 넘긴다. 사실상 2번째 인자와 밀접한 관계이다. TCP를 선택하였다면, 당연히 IPPROTO_TCP가 될 것이다.
	//					UDP를 선택하였다면, 당연히 IPPROTO_UDP가 될것이다
	// hlisten은 -1또는 socket 넘버가 들어가게 될것이다. 즉, socket system call은 소켓생성에 실패할 경우 -1을, 
	// 성공한다면 0이상의 socket descriptor를 반환할 것이다.
	// 사실 윈도우에서는 descriptor가 없다. 커널에서 다루는 소켓은 디스크립터가 아니고 핸들이다.하지만, unix계열과의 이식성을 고려해,
	// 다른핸들과는 다르게 특별히! 소켓은 unsigned int형으로 다뤄진다.

	SOCKADDR_IN tListenAddr = {}; //이 구조체는 로컬 또는 원격 주소정보를 저장하게된다. 여기서는 hListen, 즉, 서버의 주소정보를 저장하는 구조체이다.
	tListenAddr.sin_family = AF_INET; // sin_family는 domin을 의미한다. AF_INET은 이미 define되어있는 값인데, TCP,UDP,etc에서 정의되어 있다. 즉 모두 AF_INET을 사용해야한다.
	tListenAddr.sin_port = htons(PORT); // htons 는 리틀엔디안을 빅엔디안으로 변경하는 것인데, 이는 메모리에 데이터를 저장하는 방법이다.
										// 대형pc가 아닌 일반PC는 (주로 인텔) 리틀엔디안방식으로 데이터를 저장한다 . 예를 들어 1234 5678을 7856 3421로 저장하는 방법
										// 네트워크의 표준은 빅엔디안이므로 htonl htons 등으로 빅엔디안으로 변경하여, port와 주소를 저장한다.
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 서버의 주소정보이므로, 서버컴퓨터, 즉 지금 사용중인 컴퓨터의 IP주소를 입력해야한다. 따라서
													//   INADDR_ANY값(내 주소)를 넣어준다. 하지만, listen 소켓과 서버를 따로 구분한다면, 내 주소가 아닐수도있다.
													// 이또한, 빅엔디안으로 변경하며, sin_addr뒤의 s_addr은 IPv4 internet address 를 뜻한다.


	//현재까지 변수관계를 정리하자면, 
	// server의 listen소켓은 hListen이며,
	// 이에관한 정보를 담고 있는 것은 tListenAddr이다.

	//서버소켓은 소켓생성 - bind - listen - accept - 데이터교환 - close의 순서로 이루어진다. 여태까지 소켓의 초기화와 생성을 했다면, 이제 bind 해야한다.

	
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	// bind함수는 3가지 인자를 받는다.
	// 첫번째 인자는 , bind할 소켓을 전달한다.
	// 두번째 인자는 , bind할 소켓의 주소정보 구조체의 주소를 전달한다.
	// 세번째 인자는 , 두번째인자의 크기이다.
	// bind 함수의 역할 - hListen 소켓과 tListenAddr(우리가 hListen소켓과 연결을 의도한 주소정보 구조체)의 연결
	
	//여기까지하면, bind 즉 listen소켓을 생성하고, listen소켓의 역할을 할 수 있도록 정보까지 입력한 상태
	// listen소켓을 활용해보자. 즉, listen(들어오는 요청에 대하여 듣고) accept의 역할을 수행시켜보자.

	listen(hListen, SOMAXCONN);
	// listen소켓을 매개변수1로 줘, SOMAXCONN 즉, 동시 소켓 접속승인 최대치까지 listen이 가능하도록 열어놓는다.
	// 이 때부터, listen소켓을 통해 서버가 클라이언트의 연결을 수신가능한 상태로 놓는다. 이 상태를 소켓 접속 대기 상태라고 한다.

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);
	//이제 listen 중이던 hListen 소켓에 접속한 클라이언트가 생긴것이다. 
	// 생겼다면, accept(접속승인)하는 역할을 수행한다.
	// hClient는 서버에서 필요한 두번째 소켓으로, 접속승인한 클라이언트를 바로 연결해준다. 즉, 접속한 클라이언트와 연결되어 있는 소켓이다.
	// 접속한 클라이언트도 주소정보를 가지고있을것이다. 그것은 클라이언트 쪽에서 입력해서 왔을것이다.
	// 그 내용은 클라이언트 쪽에서 설명하겠지만, 아마도 서버와 마찬가지로 domain, port,ip아니겠는가?
	// accopt는 bind와 유사하다. 이유는 ? bind는 listen소켓에 listen서버의 주소정보를 연결한다.
	// accept는 hClient소켓(클라이언트와 연결하는 소켓)에 들어온 클라이언트 주소정보를 연결한다.
	// 거의 같은역할이기때문이다. 하지만, 왜 accept의 세번째인자는 주소정보로 클라이언트 주소의 크기를 받는지는 모르겠다 ㅋㅋ

	char cBuffer[PACKET_SIZE] = {};
	recv(hClient, cBuffer, PACKET_SIZE, 0);
	std::cout << cBuffer;

	char sBuffer[] = "서버도 응답해주었다^^";
	send(hClient, sBuffer, strlen(sBuffer), 0);

	//소켓은 사용 후에 순서대로 모두 해제한다.
	closesocket(hClient);
	closesocket(hListen);


	WSACleanup(); // 사용한 윈속을 해제한다.
	
	return 0;



}
