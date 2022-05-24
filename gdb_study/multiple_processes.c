#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	printf("begin!\n");
	if (fork() != 0) {
		printf("我是父进程：pid=%d,ppid=%d\n", getpid(), getppid());
		int ii = 0;
		for (ii = 0; ii < 10; ++ii) {
			printf("ii=%d\n", ii);
			sleep(1);
		}
		exit(0);
	}	
	else {
		printf("我是子进程：pid=%d, ppid=%d\n", getpid(), getppid());
		int jj = 0;
		for (jj = 0; jj < 10; ++jj) {
			printf("jj=%d\n", jj);
			sleep(1);
		}
		exit(0);
	}
	
	return 0;
}
