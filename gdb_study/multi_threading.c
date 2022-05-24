#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// x 用于线程一
// y 用于线程二
int x = 0, y = 0;

pthread_t pthid1, pthid2;

// 线程主函数
void *pth1_main(void *arg);
void *pth2_main(void *arg);

// main 函数
int main(){
	
	if(pthread_create(&pthid1, NULL, pth1_main,(void*)0) != 0)
	{
		printf("pthread_create pthid1 failed.\n");
		return -1;
	}
	
	if(pthread_create(&pthid2, NULL, pth2_main,(void*)0) != 0)
	{
		printf("pthread_create pthid2 failed.\n");
		return -1;
	}
	printf("111\n");
	pthread_join(pthid1, NULL);

	printf("222\n");
	pthread_join(pthid2, NULL);

	printf("333\n");

	return 0;
}

// 第一个线程的主函数
void *pth1_main(void * arg)
{
	for(x = 0; x < 100; ++x)
	{
		printf("x=%d\n", x);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *pth2_main(void * arg)
{
	for(y = 0; y < 100; ++y)
	{
		printf("y=%d\n", y);
		sleep(1);
	}
	pthread_exit(NULL);
}
