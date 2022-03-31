
// 1. 쓰레드

// # 1.1.pthread_create

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine)(void *), void *arg);

// 쓰레드 생성에 사용되는 함수로
// 첫 번째 아규먼트는 쓰레드 생성 시 식별을 위해서 사용되는 쓰레드 식별자이고,
// 두 번째 아규먼트는 쓰레드 특성을 지정하기 위해서 사용하며, 기본 쓰레드의 특성을 이용하고자 할 경우엔 NULL값을 사용한다. 
// 세 번째 아규먼트는 분기시켜 실행할 쓰레드 함수이며, 
// 네 번째 아규먼트는 쓰레드 함수의 인자이다.


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

	// 쓰레드 함수
void *t_function(void *data)
{
	int id;
	int i = 0;
	id = *((int *)data);

	while (1)
	{
		printf("%d : %d\n", id, i);
		i++;
		sleep(1);
	}
}

int main()
{
	pthread_t p_thread[2];
	int thr_id;
	int status;
	int a = 1;
	int b = 2;

	// 쓰레드 생성 아규먼트로 인자 1 을 넘긴다.  
	thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// 쓰레드 생성 아규먼트로 인자 2 를 넘긴다. 
	thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// 쓰레드의 종료를 기다린다. 
	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	return 0;
}

// 실행된 쓰레드는 자원을 해제시키는 함수를 이용해 쓰레드 종료 때까지 기다려야 한다.



// # 1.2.pthread_join

#include <pthread.h>
int pthread_join(pthread_t th, void **thread_return);

// 쓰레드 자원을 해제시키는 함수
// 첫 번째 아규먼트는 기다릴 쓰레드 식별자이며, 
// 두 번째 아규먼트는 리턴 값이다.
// 리턴 값이 NULL 이 아닐 경우 해당 포인터로 쓰레드 리턴 값을 받아올 수 있다.


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수 
// 1초를 기다린 후, 아규먼트^2 을 리턴한다. 
void *t_function(void *data)
{
	int num = *((int *)data);
	printf("num %d\n", num);
	sleep(1);
	return (void *)(num*num);
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
	// 쓰레드 식별자(p_thread)의 종료를 기다렸다 리턴 값을 가져온다.
	pthread_join(p_thread, (void *)&status);
	printf("thread join : %d\n", status);

	return 0;
}



// # 1.3.pthread_detach

int pthread_detach(pthread_t th);

// main 쓰레드에서 pthread_create 함수를 이용해 생성된 쓰레드를 분리시킨다.
// 식별번호 'th'인 쓰레드를 detach 시키는데, 
// detach 되었을 경우나 해당 쓰레드가 종료될 경우 
// pthread_join 함수를 호출하지 않더라도 즉시 모든 자원이 해제된다.


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

	// 쓰레드 함수
	// 1초를 기다린 후, 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
	char a[100000];
	int num = *((int *)data);
	printf("Thread Start\n");
	sleep(5);
	printf("Thread end\n");
}

int main()
{
	pthread_t p_thread;
	int thr_id;
	int status;
	int a = 100;

	printf("Before Thread\n");
	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	// 식별번호 p_thread 를 가지는 쓰레드를 detach 시켜준다.

	pthread_detach(p_thread);
	pause();
	return 0;
}

// 해당 코드에서 detach 를 사용하지 않을 경우, t_function 함수가 종료가 되더라도 자원이 해제되지 않는다.



// # 1.4.pthread_exit

void pthread_exit(void *retval);

// 현재 실행 중인 쓰레드를 종료시키고자 할 때 사용하는 함수이다.
// pthread_cleanup_push 함수가 정의되어 있다면, 
// 해당 함수가 호출될 경우 cleanup handler(메모리 정리)가 호출된다.


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

	// 쓰레드 함수
	// 1초를 기다린 후, 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
	int num = *((int *)data);
	int i = 0;
	while (1)
	{
		if (i == 3)
			pthread_exit(0);
		printf("loop %d\n", i);
		i++;
		sleep(1);
	}
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
	return 0;
}



// # 1.5.pthread_cleanup_push

void pthread_cleanup_push(void(*routine) (void *), void *arg);

// cleanup handlers 를 인스톨하기 위해 사용되는 함수.
// pthread_exit(3)(현재 실행 중인 쓰레드를 종료시킴)가 호출되어서 쓰레드가 종료될 때,
// 해당 함수에 의해서 인스톨 된 함수가 호출된다.
// routine은 쓰레드가 종료될 때 호출되는 함수이고, arg는 아규먼트이다.

// * cleanup handler *
// mutex 영역에서 pthread_exit 함수가 호출될 경우 다른 쓰레드에서 영원히 block 될수 있기 때문에,
// 자원을 되돌려주거나, mutex 잠금 등의 해제를 위한 용도로 사용된다.
// 또한 malloc 으로 할당받은 메모리, 열린 파일지정자를 닫기 위해서 사용하기도 한다.


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

char *mydata;
void cleanup(void *);

// 쓰레드 함수
// 1초를 기다린후 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
	int num = *((int *)data);
	int i = 0;
	int a = 1;
	// cleanup handler 로 cleanup 함수를 지정한다. 

	pthread_cleanup_push(cleanup, (void *)&a);
	mydata = (char *)malloc(1000);
	while (1)
	{
		if (i == 3)
		{
			// pthread_exit 가 호출되면서 cleanup 을 호출한다. 
			pthread_exit(0);
			return 1;
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



// # 1.6.pthread_cleanup_pop

void pthread_cleanup_pop(int execute);

// pthread_cleanup_push 함수와 함께 사용되며(같은 함수 내 같은 레벨의 블럭에서 한 쌍으로 사용해야 함), 
// install 된 cleanup handler 을 제거하기 위해 사용된다.
// execute 가 0 일 경우, pthread_cleanup_push 에 의해 install 된 cleanup handler 를(실행 x)삭제시키고, 
// 0 이 아닐 경우 cleanup handler 을 실행시키고 삭제된다..



// # 1.7.pthread_self

pthread_t pthread_self(void);

// 해당 함수를 호출하는 현재 쓰레드의 식별자 값을 리턴한다.


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



// --- 쓰레드 동기화 함수 ---

// # 2.1.pthread_mutex_init

// * mutex */
// MUTual EXclusion (=상호 배제)
// mutex 는 여러 개의 쓰레드가 공유하는 데이터를 보호하기 위해서 사용되는 도구로써,
// 보호하고자 하는 데이터를 다루는 코드 영역을 한 번에 하나의 쓰레드만 실행 가능하도록 하는 방법으로,
// 공유되는 데이터를 보호한다.
// 이런 코드 영역(하나의 쓰레드만 점유 가능)을 critical section 이라 하며, 
// mutex 관련 API 를 이용해 관리할 수 있다.


int pthread_mutex_init(pthread_mutex_t * mutex,
	const pthread_mutex_attr *attr);

// mutex 객체를 초기화 시키기 위해서 사용하는 함수이다.
// 첫 번째 인자로 mutex를 초기화시키며, 
// 두 번째 인자로 mutex 특성을 변경할수 있다.
// 기본 mutex 특성을 이용할 경우엔 NULL 을 사용하면 된다.

// * mutex 특성(종류) * 
// [ "fast", "recurisev", "error checking" ]
// 기본은 "fast"


// 뮤텍스 객체 선언
pthread_mutex_t mutex_lock;
...
void *t_function()
{
	pthread_mutex_lock(&mutex_lock);
	// critical section
	pthread_mutex_unlock(&mutex_lock);
}
int main()
{
	pthread_t p_thread;
	int state;
	// 뮤텍스 객체 초기화(기본 특성)
	pthread_mutex_init(&mutex_lock, NULL);
	pthread_create(&p_thread, NULL, t_function, (void *)&a);
	...
		pthread_join(&p_thread, (void **)&status);
}



// # 2.2.pthread_mutex_destroy

int pthread_mutex_destroy(pthread_mutex_t *mutex);

// 인자로 주어진 mutex 객체를 제거하기 위해서 사용되는 함수.
// mutex 는 pthread_mutex_init() 함수(뮤택스 객체를 초기화 함)를 이용해 생성된 뮤텍스 객체이다.
// pthread_mutex_destroy 함수를 이용해 mutex 를 삭제하려면 
// 해당 mutex 는 반드시 unlock 상태여야 한다.



// # 2.3.pthread_mutex_lock

int pthread_mutex_lock(pthread_mutex_t *mutex);

// critcal section(임계 영역) 에 들어가기 위해서 mutex lock 을 요청하는 함수이다.
// 이미 다른 쓰레드에서 mutex lock 를 얻어서 사용하고 있을 경우,
// 다른 쓰레드에서 mutex lock 을 해제할 때까지 block 되며,
// 다른 쓰레드에서 mutex lock 을 사용하고 있지 않다면, 
// 즉시 mutex lock 을 얻을 수 있고  critcal section 에 진입하게 된다.
// 만약 critcal section 에서의 작업을 마쳐 사용하고 있는 mutex lock 이 필요 없을 경우 
// pthread_mutex_unlock 함수를 호출해 mtuex lock 를 되돌려준다.



// # 2.4.pthread_mutex_unlock

int pthread_mutex_unlock(pthread_mutex_t *mutex);

// critical section 에서 모든 작업을 마치고 mutex lock 을 돌려주기 위해 사용하는 함수이다.
// 해당 함수를 이용해 mutex lock 를 되돌려주면 다른 쓰레드에서 mutex lock 을 얻을 수 있는 상태가 된다.



// # 2.5.pthread_cond_init

int pthread_cond_init(pthread_cond_t *cond,
	const pthread_cond_attr *attr);

// 조건 변수(condition variable) 'cond' 를 초기화하기 위해서 사용하는 함수이다. 
// (상수 PTHREAD_COND_INITIALIZER로 초기화 또한 가능)
// 인자 attr 를 이용해 조건변수의 특성을 변경할 수 있으며, 
// NULL 값을 줄 경우 기본 특성으로 초기화된다.

// ex)

/*
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
or
pthread_cond_init(&cond, NULL);

*/



// # 2.6.pthread_cond_signal

int pthread_cond_signal(pthread_cond_t *cond);

// 조건 변수 'cond' 에 signal을 보내는 함수이다.
// signal 을 보낼 경우 cond 에서 wait 중인 쓰레드가 있다면 쓰레드를 깨우게 된다.(봉쇄 해제)
// cond 를 기다리는 쓰레드가 없을 경우엔 아무 일도 일어나지 않는다.
// 여러 개의 쓰레드가 기다리고 있을 경우엔 그 중 하나의 쓰레드에게만 전달된다.
// 다만, 어떤 쓰레드에게 신호가 전달될 지 알 수 없다.



// # 2.7.pthread_cond_boradcast

int pthread_cond_broadcast(pthread_cond_t *cond);

// 조건 변수 'cond' 에서 기다리는(wait) 모든 쓰레드에게 신호를 보내 깨운다는 점을 제외하고는 pthread_cond_signal과 동일하게 작동한다.



// # 2.8.pthread_cond_wait

int pthread_cond_wait(pthread_cond_t cond, pthread_mutex_t *mutex);

// 조건 변수 'cond' 를 통해서 신호가 전달될 때까지 block 되는 함수이다.
// 신호가 전달되지 않을 경우 영원히 block 될 수 있으며,
// block 되기 전 mutex 잠금을 자동으로 되돌려준다.



// # 2.9.pthread_cond_timewait

int pthread_cond_timedwait(pthread_cont_t *cond, pthread_mutex_t *mutex,
	const struct timespec *abstime);

// 조건 변수 'cond' 를 통해 신호가 전달될 때까지 block 되며 
// 자동으로 mutex을 돌려주는 점에서 pthread_cond_wait와 동일하다.
// 그러나 시간 체크가 가능해 abstime(절대 시간) 동안 신호가 도착하지 않는다면, error 를 발생하며 리턴한다.
// 이 때, 리턴 값은 ETIMEDOUT 이다. (연결이 타임아웃 되어 발생하는 오류)
// errno(오류 번호)가 아닌, 리턴 값으로 에러가 넘어오기 때문에 주의해야 한다.

// 또, 다른 signal 에 의해서 interrupted 될 수 있으며 이때 EINTR 을 리턴한다. 
// (시스템 수행 중 interrupt가 걸려 수행이 중단된 경우 발생하는 오류)
// 때문에 해당 함수 사용 시 interrupted 상황에 대한 처리를 해주어야 한다.



// # 2.10.pthread_cond_destroy

int pthread_cond_destroy(pthread_cond_t *cond);

// pthread_cond_init을 통해 생성한 조건 변수 'cond' 에 대한 자원을 해제하는 함수이다.
// 해당 함수를 호출하기 전 어떤 쓰레드도 cond 에서의 시그널을 기다리지 않는 걸 확인해야 한다.
// 만약 cond 시그널을 기다리는 쓰레드가 존재할 경우 이 함수는 실패하고 EBUSY 를 리턴한다.
// (해당 파일을 읽거나 쓸 수 없는 상태에 발생하는 오류)


// --- ping / pong 쓰레드가 번갈아가며 "ping", "pong" 을 날리는 프로그램 ---

// pong 쓰레드 시그널 대기 -> ping 쓰레드 ciritical section 진입 후 "ping" 출력 및 시그널 발생 -> pong 쓰레드 "pong" 출력 후 시그널 발생 전까지 시그널 대기


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

void *ping(void *);
void *pong(void *);

pthread_mutex_t sync_mutex;
pthread_cond_t  sync_cond;

pthread_mutex_t gmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  gcond = PTHREAD_COND_INITIALIZER;

int main()
{
	vector<void *(*)(void *)> thread_list;
	vector<pthread_t> tident(10);
	int thresult;
	int status;
	int i;

	pthread_mutex_init(&sync_mutex, NULL);
	pthread_cond_init(&sync_cond, NULL);

	thread_list.push_back(pong);
	thread_list.push_back(ping);

	for (i = 0; i < thread_list.size(); i++)
	{
		pthread_mutex_lock(&sync_mutex);
		if (pthread_create(&tident[i], NULL, thread_list[i], (void *)NULL) < 0)
		{
			perror("error:");
			exit(0);
		}
		pthread_cond_wait(&sync_cond, &sync_mutex);
		pthread_mutex_unlock(&sync_mutex);
	}
	for (i = 0; i < tident.size(); i++)
	{
		pthread_join(tident[i], (void **)&status);
	}
}

void *ping(void *data)
{
	int i = 0;
	pthread_mutex_lock(&sync_mutex);
	pthread_cond_signal(&sync_cond);
	pthread_mutex_unlock(&sync_mutex);
	while (1)
	{
		// critical section 1
		pthread_mutex_lock(&gmutex);
		printf("%d : ping\n", i);
		pthread_cond_signal(&gcond);  // 쓰레드 동기화
		pthread_cond_wait(&gcond, &gmutex);
		pthread_mutex_unlock(&gmutex);
		usleep(random() % 100);
		i++;
	}
}


void *pong(void *data)
{
	int i = 0;
	pthread_mutex_lock(&sync_mutex);
	sleep(1);
	pthread_cond_signal(&sync_cond);
	pthread_mutex_unlock(&sync_mutex);
	while (1)
	{
		// critical section 2
		pthread_mutex_lock(&gmutex);
		pthread_cond_wait(&gcond, &gmutex);
		printf("%d : pong\n", i);
		pthread_cond_signal(&gcond);  // 쓰레드 동기화
		pthread_mutex_unlock(&gmutex);
		i++;
	}
}

// ping가 먼저 critical section에 진입할 경우 시그널 대기로 인해 mutex 잠금이 해제되고 
// 뒤늦게 진입하려던 pong 쓰레드는 ping 신호를 기다리며 시그널 대기를 무한정으로 하며 교착상태에 빠질 수 있다.
// -> 쓰레드 간 동기화를 이용해 해결 가능



// 3. 쓰레드 속성 (thread attribute)

// # 3.1.pthread_attr_init

int pthread_attr_init(pthread_attr_t *attr);

// thread attribute 객체인 attr을 디폴트 값으로 초기화 시키는 함수.
// 성공할 경우 0, 실패할 경우 - 1 을 리턴한다.



// # 3.2.pthread_attr_distroy

int pthread_attr_destroy(pthread_attr_t *attr);

// pthread_attr_init 함수에 의해 생성된 thread attribute 객체인 attr을 제거하는 함수이다.
// 제거된 attr 을 다시 사용해야 할 경우 pthread_attr_init 함수를 이용해서 다시 초기화 해야 한다.



// # 3.3.pthread_attr_getscope

int pthread_attr_getscope(const pthread_attr_t *attr, int *scope);

// 쓰레드가 다루어지고 있는 영역(scope) 얻어오기 위해서 사용되는 함수이다.
// 영역은 'PTHREAD_SCOPE_SYSTEM', 'PTHREAD_SCOPE_PROCESS' 이 있다.

// SYSTEM 영역의 쓰레드 = user 모드 쓰레드 (단일 프로세스 내에서만 가능)
// PROCESS 쓰레드 = 커널 모드 쓰레드 

// Linux -> 유저모드 쓰레드
// 커널에서 쓰레드를 스케줄링하는 방식이 아닌 쓰레드 라이브러리를 통해 쓰레드를 스케줄링 하는 방식을 사용한다.


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
		printf("user mode thread\n");  // Linux
	}
	else if (scope == PTHREAD_SCOPE_PROCESS)
	{
		printf("Kernel mode thread\n");  // Solaris
	}

	return 1;
}

// OS에 따라 컴파일 결과가 다름



// # 3.4.pthread_attr_setscope

int pthread_attr_setscope(pthread_attr_t *attr, int scope);

// 쓰레드가 어떤 영역(scope)에서 작동하게 할 것인지 결정하기 위해 사용하는 함수이다.

// Linux -> 커널 모드 쓰레드를 지원하지 않기에 PTHREAD_SCOPE_SYSTEM 만 선택 가능.
// Solaris -> 유저 모드와 커널 모드 중 선택 가능.


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	pthread_attr_t pattr;
	int scope;

	pthread_attr_init(&pattr);

	pthread_attr_setscope(&pattr, PTHREAD_SCOPE_PROCESS);  // 커널 모드 선택
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

// OS에 따라 컴파일 결과가 다름



// # 3.5.pthread_attr_getdetachstate

int pthread_attr_getdetachstate(pthread_attr_t *attr, int detachstate);

// 쓰레드가 join 가능한 상태(PTHREAD_CREATE_JOINABLE) 인지 detached 상태인지(PTHREAD_CREATE_DETACHED) 인지를 알아내는 함수이다.
// 알아낸 값은 아규먼트 'detachstate' 에 저장된다.

// 디폴트 값은 PTHREAD_CREATE_JOINABLE 이며,
// pthread_detach 함수를 이용해 생성된 쓰레드를 detach 상태로 만들었을 경우
// 혹은 pthread_attr_setdetachstate 함수를 이용해 쓰레드를 detach 상태로 변경시켰을 경우 PTHREAD_CREATE_DETACHED 상태가 된다.


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_attr_t attr;

void *test(void *a)
{
	int policy;
	printf("Thread Create\n");
	pthread_attr_getdetachstate(&attr, &policy);  // 디폴트
	if (policy == PTHREAD_CREATE_JOINABLE)
	{
		printf("Join able\n");
	}
	else if (policy == PTHREAD_CREATE_DETACHED)
	{
		printf("Detace\n");
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

// "Join able" 출력



// # 3.6.pthread_attr_setdetachstate

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);

// 쓰레드의 상태를 PTHREAD_CREATE_JOINABLE 혹은 PTHREAD_CREATE_DETACHED 상태로 변경시키기 위해서 사용되는 함수이다.

// * 사용 방법 *
/*
pthread_attr_t attr;
...
// JOINABLE 상태로 변경하고자 할 경우
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

// DETACHED 상태로 변경하고자 할 경우
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

*/



// 4. 쓰레드 시그널 관련

// 프로세스에 시그널이 전달되면 프로세스가 생성된 모든 쓰레드로 시그널이 전달된다.


// # 4.1.pthread_sigmask

#include <pthread.h>
#include <signal.h>

int pthread_sigmask(int how, const sigset_t *newmask, sigset_t *oldmask);

// 특정 쓰레드만 시그널을 받도록 하고 싶을 경우 사용하는 함수이다.



// # 4.2.pthread_kill

#include <pthread.h>
#include <signal.h>

int pthread_kill(pthread_t thread, int signo);

// 쓰레드 식별번호인 'thread'로 'signo' 번호의 시그널을 전달한다.



// # 4.3.sigwait

#include <pthread.h>
#include >signal.h>

int sigwait(const sigset_t *set, int *sig);

// 시그널 전달을 동기적으로 기다리는 함수이다.



// 5. 쓰레드 취소

// # 5.1.pthread_cancel

#include <pthread.h>

int pthread_cancel(pthread_t thread);


// # 5.2.pthread_setcancelstate

#include <pthread.h>

int pthread_setcancelstate(int state, int *oldstate);


// # 5.3.pthread_setcancelstate

// # #include <pthread.h>

int pthread_setcancelstate(int state, int *oldstate);


// # 5.4.pthread_setcanceltype

// # #include <pthread.h>

int pthread_setcanceltype(int type, int *oldtype);


// # 5.5.pthread_testcancel

#include <pthread.h>

void pthread_testcancel(void);
