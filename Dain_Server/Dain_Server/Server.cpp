#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library


int main(int argc, char *argv[])
{

	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	int c, cnt;
	char msg[100];

	printf("\nInitialising Winsock...");
	//에러 처리1
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//소켓 생성 불능 에러
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	//소켓 생성
	printf("Socket created.\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8888);



	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}
	puts("Bind done");
	listen(s, 3);


	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
	}

	puts("Connection accepted");
	//문자를 계속 전송할 수 있도록 반복문 구성
	while (1) {
		printf("Me: ");
		gets(msg);
		//메시지를 클라이언트로 전송
		send(new_socket, msg, strlen(msg), 0);
	}

	//send(new_socket , msg , strlen(msg) , 0);
	return 0;
}