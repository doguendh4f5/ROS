#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

	pthread_attr_t attr;
void *test(void *a)
{
	int policy;
	printf("Thread Create\n");
	pthread_attr_getdetachstate(&attr, &policy);
	if (policy == PTHREAD_CREATE_JOINABLE)
	{
		printf("Join able\n");
	}
	else if (policy == PTHREAD_CREATE_DETACHED)
	{
		printf("Detache\n");
	}
}
int main()
{
	int status;
	pthread_t p_thread;
	pthread_attr_init(&attr);
	if (pthread_create(&p_thread, NULL, test, (void *)NULL) < 0)
	{
		exit(0);
	}

	pthread_join(p_thread, (void **)&status);
}
