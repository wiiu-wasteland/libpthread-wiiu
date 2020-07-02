#include <sched.h>
#include <coreinit/thread.h>

int sched_yield(void)
{
	OSYieldThread();
	return 0;
} 
