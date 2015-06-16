#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define REUSE

void sighandler(int);
void reuse_option_set(int);
void* con_from_c(void*);

int main(int argc, char** argv)
{
	int sock_s, sock_c;
	struct sockaddr_in addr_s, addr_c;
	int addr_len;
	struct sigaction sa;
	pthread_t p_thread;

	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTSTP, &sa, 0);

	sock_s = socket(AF_INET, SOCK_STREAM, 0);
	reuse_option_set(sock_s);

	bzero(&addr_s, sizeof(addr_s));
	addr_s.sin_family = AF_INET;
	addr_s.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_s.sin_port = htons(7575);

	bind(sock_s, (struct sockaddr*)&addr_s, sizeof(addr_s));
	listen(sock_s, 5);

	while (1)
	{
		addr_len = sizeof(addr_c);
		sock_c = accept(sock_s, (struct sockaddr*)&addr_c, &addr_len);
		pthread_create(&p_thread, NULL, (void*)con_from_c, (void*)&sock_c);
	}

	return 0;
}

void sighandler(int signum)
{
	if (signum == SIGTSTP)
	{
		exit(0);
	}
}

void reuse_option_set(int sock)
{
	int optval = 0;
	socklen_t optlen;
	optlen = sizeof(optlen);

#ifdef REUSE
	optval = 1;
#else
	optval = 0;
#endif
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void* con_from_c(void* sock)
{
	char message[1024];
	int sock_c = *((int*)sock);
	int message_len;

	memset(message, 0x00, 1024);

	printf("socket %d\n", sock_c);
	while (1)
	{
		message_len = read(sock_c, message, sizeof(message));
		printf("read byte %d\n", message_len);
		if (message_len <= 0)
		{
			printf("read a byte and break\n");
			break;
		}
	}
	if (shutdown(sock_c, SHUT_RDWR) == 0)
	{
		fd_set readfds;
		fd_set errorfds;
		struct timeval timeout;
		FD_ZERO(&readfds);
		FD_ZERO(&errorfds);
		FD_SET(sock_c, &readfds);
		FD_SET(sock_c, &errorfds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		select(1, &readfds, NULL, &errorfds, &timeout);
	}
	if (close(sock_c) != -1)
	{
		printf("close successfully\n");
	}
	else
	{
		printf("close failure\n");
	}
	return 0;
}