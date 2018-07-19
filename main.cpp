#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string>
#include <netinet/in.h>
#include <sstream>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>
#include <thread>
#include "distribute.h"
void client(int client_sockfd,sockaddr_in client_sockaddr) {
	distribute main;
	std::string bufs,reply;
	char clientip[64],buf[4096];
	memset(buf, 0, 4096);
	memset(clientip, 0, 64);
	main.ip = inet_ntop(AF_INET, &client_sockaddr.sin_addr, clientip, 64);
	sleep(1);
	main.u.ip = main.ip;
	//send(client_sockfd, FUHAO, 4096, 0);
	while (recv(client_sockfd, buf, 4096, 0) > 0) {
		std::cout <<"["<<clientip<< "] [COMMAND] "<<buf<< std::endl;
		//send(client_sockfd, "process$Processing...", 4096, 0);
		bufs = buf;
		if (bufs != "exit")
		{
			reply = main.input(bufs).c_str();
			send(client_sockfd, reply.c_str(), 1024, 0);
			std::cout << "[" << clientip << "] [REPLY] " << reply << std::endl;
			memset(buf, 0, 4096);
			usleep(80000);
		}
		else
		{
			std::cout << "[" << clientip << "] [EXIT] "<<std::endl;
			break;
		}
	}
	close(client_sockfd);
	std::cout << "[SERVER] Disconnected   IP:" << clientip << std::endl;
}

int main()
{
	system("mkdir data");
	std::cout << "[SERVER] Starting"<< std::endl;
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct  sockaddr_in server_sockaddr, client_sockaddr;
	signal(SIGPIPE, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(8863);
	std::cout << "[SERVER] PORT:8863" << std::endl;
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_len = sizeof(server_sockaddr);
	int on;
	setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (bind(server_sockfd, (struct sockaddr*)&server_sockaddr, server_len) == -1) {
		printf("bind error");
		exit(1);
	}
	std::cout << "[SERVER] [Done]Bind" << std::endl;
	if (listen(server_sockfd, 5) == -1) {
		printf("listen error");
		exit(1);
	}
	std::cout << "[SERVER] [Done]Listening..." << std::endl;
	client_len = sizeof(client_sockaddr);
	while (1) {
		if ((client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_sockaddr, &client_len)) == -1) {
			printf("connect error");
			exit(1);
		}
		else {
			char ip[64];
			inet_ntop(AF_INET, &client_sockaddr.sin_addr, ip, 1024);
			std::cout << "[SERVER] NewConnected IP:" << ip << std::endl;
			std::thread t(client, client_sockfd, client_sockaddr);
			t.detach();
		}
	}
	close(server_sockfd);
    return 0;
}