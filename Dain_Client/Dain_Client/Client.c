#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
//소켓 함수 관련 헤더 파일(그 전에 ws2_32.lib를 링크해야됨.)
#include <winsock2.h>
#include <time.h>
#pragma comment (lib, "ws2_32.lib")
void timer(int);

int main(int argc, char *argv[])
{

	WSADATA wsa;
	//소켓 구조체
	SOCKET sck;
	int cnt;
	struct sockaddr_in ip_info;
	char server_reply[2000];
	int recv_size;



	printf("Installing");
	for (cnt = 1; cnt <= 3; cnt++){
		timer(1);
		printf(".");
	}


	//에러 처리1
	if (WSAStartup(MAKEWORD(2, 2), &wsa) == INVALID_SOCKET)
		printf("WSA error\n");
	//에러 처리2
	else if ((sck = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		printf("Socket error\n");
	else{
		ip_info.sin_addr.s_addr = inet_addr("127.0.0.1");
		ip_info.sin_family = AF_INET;
		ip_info.sin_port = htons(8888);
	}

	//에러 처리3
	if (connect(sck, (struct sockaddr *)&ip_info, sizeof(ip_info)) < 0)
		printf("\nNot connected\n");
	else
		printf("\nSession is up\n");

	//서버에서 특정 문자를 입력 받을 때까지 문자를 계속 받는다.
	while (recv_size = recv(sck, server_reply, 2000, 0)) {
		if (recv_size == SOCKET_ERROR) {
			puts("recv failed");
			break;
		}
		//에러가 없으면 서버에서 보낸 메시지를 계속 출력
		else {
			server_reply[recv_size] = '\0';
			puts(server_reply);
		}
	}




	_getch();
	return 0;
}


// Timer function: 
void timer(int sec)
{
	clock_t end;

	end = clock() + sec * CLOCKS_PER_SEC;
	while (clock() <= end);
}