#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 8765

int main() {
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	int clicent_fd = 0;
	char clientip[1024];
	if (sock_fd == -1) {
		perror("sockfd create error");
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8765);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));

	listen(sock_fd, 20);

	struct sockaddr_in clicent_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERV_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len = sizeof(addr);
	clicent_fd = accept(sock_fd, (struct sockaddr*)&clicent_addr, &len);
	if (clicent_fd == -1) {
		perror("server accept error:");
	}
	printf("server, clicent address:%s, port:%d\n", 
							inet_ntop(AF_INET, &clicent_addr.sin_addr.s_addr, clientip, 1024), 
							ntohs(clicent_addr.sin_port));
	int index = 10;
	while (index--) {
	char temp[1024];
		int ret = read(clicent_fd, temp, 100);
		printf("server receive:%s\n", temp);
		for (int i = 0; i < ret; i++) {
			temp[i] = temp[i] - 'a' + 'A';
		}
		write(clicent_fd, temp, ret);
	}
	close(clicent_fd);
	close(sock_fd);



	return 0;
}
