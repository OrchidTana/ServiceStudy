#include <iostream>
#include <unistd.h>
#include<cstring>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8111
#define MESSAGE_LEN	1024

int main(int argc, char** argv) {

	int socket_fd;
	int ret = -1;
	struct sockaddr_in serveraddr;
	char sendbuf[MESSAGE_LEN] = {0, };
	char recvbuf[MESSAGE_LEN] = {0, };
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0) {
		std::cout << "Failed to create socket!" << std::endl;
		exit(-1);
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = PORT;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(socket_fd, 
					(struct sockaddr*)&serveraddr, 
					sizeof(struct sockaddr));
	if(ret < 0)	{
		std::cout << "Failed to connect server!" << std::endl;
		exit(-1);
	}

	while(1) {
		// 将sendbuf清空
		memset(sendbuf, 0, MESSAGE_LEN);
		std::cout << "<<<<send message:" << std::endl;
		gets(sendbuf);
		ret = send(socket_fd, sendbuf, strlen(sendbuf), 0);
		if(ret <= 0) {
			std::cout << "Failed to send data!" << std::endl;
			break;
		}
		
		if(strcmp(sendbuf, "quit") == 0) {
			break;
		}
		std::cout << ">>> echo message:" << std::endl;
		ret = recv(socket_fd, recvbuf, MESSAGE_LEN, 0);
		recvbuf[ret] = '\0';
		std::cout << "recv: " << recvbuf << std::endl;
		
	}

	close(socket_fd);
	return 0;
}
