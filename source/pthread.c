
int pthread_create(pthread_t *newthread, const pthread_attr_t *attr, void *(*start_routine)(void *arg), void *arg);

{
	uint uVar1;
	int *__s;
	pthread_t pVar2;
	int iVar3;
	OSThread *thread;
	char *name;
	pthread_t pVar4;
	undefined4 uVar5;
	uint __n;
	int *piVar6;
	byte abStack56 [24];
	
	*newthread = 0;
	if (attr == (pthread_attr_t *)0x0) {
		pthread_attr_init((pthread_attr_t *)abStack56);
		attr = (pthread_attr_t *)abStack56;
	}
	uVar1 = *(int *)(*attr + 4) + 0x1fU & 0xffffffe0;
	__n = uVar1 + 0x6e8;
	if (*(uint *)(*attr + 0x10) == 0) {
		__s = shim_allocFromHeap(0xb,__n,4);
	}
	else {
		__s = shim_allocFromHeap(*(uint *)(*attr + 0x10),__n,0x20);
	}
	if (__s == (int *)0x0) {
		return 0x12;
	}
	memset(__s,0,__n);
	pVar4 = (int)__s + uVar1;
	*newthread = pVar4;
	piVar6 = (int *)(pVar4 + 0x6a0);
	OSInitMutex((OSMutex *)(pVar4 + 0x6bc));
	if ((*attr)[9] == 0) {
		uVar5 = *(undefined4 *)(*attr + 0x14);
		*(void **)(pVar4 + 0x6b0) = arg;
		pVar2 = *newthread;
		*(undefined4 *)(pVar4 + 0x6b8) = 0;
		*(undefined4 *)(pVar4 + 0x6ac) = 0;
		*(undefined4 *)(pVar4 + 0x6b4) = uVar5;
		iVar3 = shim_CreateThread(pVar2);
	}
	else {
		uVar5 = *(undefined4 *)(*attr + 0x14);
		*(void **)(pVar4 + 0x6b0) = arg;
		pVar2 = *newthread;
		*(undefined4 *)(pVar4 + 0x6b8) = 0;
		*(undefined4 *)(pVar4 + 0x6b4) = uVar5;
		*(undefined4 *)(pVar4 + 0x6ac) = 0;
		iVar3 = shim_CreateThread(pVar2);
	}
	if (iVar3 == 1) {
		name = *(char **)(*attr + 0xc);
		if ((name == (char *)0x0) || (*name == '\0')) {
			name = "pthread_create";
		}
		OSSetThreadName((OSThread *)*newthread,name);
		thread = (OSThread *)*newthread;
		*(OSThread **)(thread->specific + 1) = thread;
		thread->specific[0] = (void *)0x0;
		OSSetThreadDeallocator(thread,FUN_0201679c);
		OSLockMutex((OSMutex *)&DAT_10008820);
		pVar2 = *newthread;
		*(int **)piVar6 = DAT_100087d0;
		if (DAT_100087d0 != (int *)0x0) {
			*(int **)((int)DAT_100087d0 + 4) = piVar6;
		}
		DAT_100087d0 = piVar6;
		*(pthread_t *)(pVar4 + 0x6a8) = pVar2;
		*(undefined4 *)(pVar4 + 0x6a4) = 0;
		OSResetEvent((OSEvent *)&DAT_100087d8);
		OSResetEvent((OSEvent *)&DAT_100087fc);
		OSUnlockMutex((OSMutex *)&DAT_10008820);
		if ((*attr)[10] == 1) {
			OSDetachThread((OSThread *)*newthread);
		}
		OSResumeThread((OSThread *)*newthread);
		return 0;
	}
	shim_freeToHeap(__s);
	return 6;
}

