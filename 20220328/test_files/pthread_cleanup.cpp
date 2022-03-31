#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

	// 쓰레드 함수
	// 1초를 기다린후 아규먼트^2 을 리턴한다.
	//

	char *mydata;
void cleanup(void *);
void *t_function(int *data)
{
	int num = *((int *)data);
	int i = 0;
	int a = 1;
	// cleanup handler 로 cleanup 함수를 
	// 지정한다. 
	pthread_cleanup_push(cleanup, (void *)&a);
	mydata = (char *)malloc(1000);
	while (1)
	{
		if (i == 3)
		{
			// pthread_exit 가 호출되면서 
			// cleanup 을 호출하게 된다. 
			pthread_exit(0);
			return (void*)1;
		}
		printf("loop %d\n", i);
		i++;
		sleep(1);
	}
	pthread_cleanup_pop(0);
}


int main()
{
	pthread_t p_thread;
	int thr_id;
	int status;
	int a = 100;


	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	pthread_join(p_thread, (void **)&status);
	printf("Join finish\n");
}

// cleanup handler
void cleanup(void *myarg)
{
	printf("thread is clean up\n");
	printf("resource free\n");
	free(mydata);
}
