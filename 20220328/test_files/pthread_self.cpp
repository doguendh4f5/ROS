#include <pthread.h>
#include <stdio.h>

	void *func(void *a)
{
	pthread_t id;
	id = pthread_self();
	printf("->%d\n", id);
}

int main(int argc, char **argv)
{
	pthread_t p_thread;
	pthread_create(&p_thread, NULL, func, (void *)NULL);
	printf("%d\n", p_thread);
	pthread_create(&p_thread, NULL, func, (void *)NULL);
	printf("%d\n", p_thread);

	return 1;
}
