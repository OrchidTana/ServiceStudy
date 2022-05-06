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
	inet_pton(AF_INET, "8.142.8.170", &(addr.sin_addr.s_addr));
	connect(sock_fd, (const struct sockaddr*)(&addr), sizeof(addr));
	int index = 10;
	while (index--) {
		char temp[8] = "abcdefg";
		write(clicent_fd, temp, 8);
	  read(clicent_fd, temp, 8);
	}
	close(sock_fd);



	return 0;
}
