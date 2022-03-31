#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
	pthread_attr_t pattr;
	int scope;

	pthread_attr_init(&pattr);

	pthread_attr_getscope(&pattr, &scope);
	if (scope == PTHREAD_SCOPE_SYSTEM)
	{
		printf("user mode thread\n");
	}
	else if (scope == PTHREAD_SCOPE_PROCESS)
	{
		printf("Kernel mode thread\n");
	}

	return 1;
}
