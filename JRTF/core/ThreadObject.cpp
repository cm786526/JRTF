#include"ThreadObject.h"

ThreadObject::ThreadObject()
{
	thread_function = NULL;
	thread_function_param = NULL;
	my_name = "Unknown";
	pthread_attr_init(&sched_attr);
	pthread_attr_setinheritsched(&sched_attr, PTHREAD_EXPLICIT_SCHED);
	set_policy_priority("other", 0);
	set_contention_scope(PTHREAD_SCOPE_SYSTEM);
	set_joinable();
}

ThreadObject::~ThreadObject()
{
}

// set the name of the thread
void ThreadObject::set_it_name(std::string name) {
	prctl(PR_SET_NAME, name.c_str());
}

void ThreadObject::run() {
	errno = pthread_create(&my_tid, &sched_attr, thread_function, thread_function_param);
	if (errno != 0) {
		std::cerr << "ThreadObject name = " << my_name << " ";
		perror("pthread_create failed!");
		exit(errno);
	}
}

void ThreadObject::join(void) {
	pthread_join(my_tid, NULL);
}

void ThreadObject::set_policy_priority(string spolicy, int priority) {
	int policy = name2policy(spolicy);
	int min = sched_get_priority_min(policy);
	int max = sched_get_priority_max(policy);
	struct sched_param param;

	if (priority<min)
		param.__sched_priority = min;
	else if (priority>max)
		param.__sched_priority = max;
	else
		param.__sched_priority = priority;

	pthread_attr_setschedpolicy(&sched_attr, policy);
	pthread_attr_setschedparam(&sched_attr, &param);
}


void ThreadObject::set_contention_scope(int Scope) {
	if (Scope == PTHREAD_SCOPE_SYSTEM) 
	{
		pthread_attr_setscope(&sched_attr, PTHREAD_SCOPE_SYSTEM);
	}else if (Scope == PTHREAD_SCOPE_PROCESS)
	{
		pthread_attr_setscope(&sched_attr, PTHREAD_SCOPE_PROCESS);
	}
}

void ThreadObject::set_detached(void) {
	pthread_attr_setdetachstate(&sched_attr, PTHREAD_CREATE_DETACHED);

}

void ThreadObject::set_joinable(void) {
	pthread_attr_setdetachstate(&sched_attr, PTHREAD_CREATE_JOINABLE);
}

void ThreadObject::set_affinity(unsigned long int cpuset) {
	if (cpuset == 0)
		return;
	cpu_set_t affinity;
	CPU_ZERO(&affinity);
	for (int i = 0; i<64; i++) {
		if ((cpuset >> i) & 1) {
			CPU_SET(i, &affinity);
		}
	}
	pthread_attr_setaffinity_np(&sched_attr, sizeof(cpu_set_t), &affinity);
}

 int ThreadObject::name2policy(string polname)
{
	if (polname == "other")
		return SCHED_OTHER;
	else if (polname == "batch")
		return SCHED_BATCH;
	else if (polname == "idle")
		return SCHED_IDLE;
	else if (polname == "fifo")
		return SCHED_FIFO;
	else if (polname == "rr")
		return SCHED_RR;
	else	/* default policy if we don't recognize the request */
		return SCHED_OTHER;
	//return SCHED_FIFO;
}

 string ThreadObject::policy2name(int policy)
{
	std::string policystr = "";

	switch (policy) {
	case SCHED_OTHER:
		policystr = "other";
		break;
	case SCHED_FIFO:
		policystr = "fifo";
		break;
	case SCHED_RR:
		policystr = "rr";
		break;
	case SCHED_BATCH:
		policystr = "batch";
		break;
	case SCHED_IDLE:
		policystr = "idle";
		break;
	}
	return policystr;
}