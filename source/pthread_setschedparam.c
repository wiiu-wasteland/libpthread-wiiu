#include <pthread.h>
#include <sched.h>
#include <coreinit/thread.h>

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param)
{
	OSSetThreadPriority(thread, param->sched_priority);
	return 0;
}
