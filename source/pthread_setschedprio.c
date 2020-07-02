#include <pthread.h>
#include <coreinit/thread.h>

int pthread_setschedprio(pthread_t thread, int prio)
{
	OSSetThreadPriority(thread, prio);
	return 0;
}
