/**
 * this program is testing for daemon
 * @author helloworld
 * @date 2022-05-27
 * @copyleft GPL 2.0
 */

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void daemonize() {
	
	pid_t pid;
	int fd = 0;	
	if ((pid = fork()) < 0) {
		std::cout << "can't create subprocess!" << std::endl;
	}else if (pid != 0) {
		exit(0);
	}
	
	setsid();	// 
	
	// change the director to the root directory
	// chdir function reference http://c.biancheng.net/cpp/html/305.html
	if (chdir("/") < 0) {
		std::cout << "can't change dir!" << std::endl;
		exit(-1);
	}
	// open the file to write the log
	fd = open("/dev/null", O_RDWR);
	// dup2函数重定向
	// 将标准输入、标准输出、标准错误重定向到fd文件描述符中
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	return;
}

int main(int argc, char* argv[]) {
	
	daemonize();

	while(1) {
		sleep(1);	// 休眠1秒
	
	}
	
	return 0;

}
