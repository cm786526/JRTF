#include"Timer.h"

static inline void tsnorm(struct timespec *ts);
Timer::Timer()
{
	timer_name = "unknown";
	timer_id = NULL;
	timer_func = NULL;
	timer_func_param = NULL;
	period = 0;
}

Timer::~Timer()
{
}

void Timer::s_timer_thread(union sigval sig_val) {
	Timer * me = (Timer *)sig_val.sival_ptr;
	me->timer_func(me->timer_func_param);

}

void Timer::s_timer_handler(int sig, siginfo_t *si, void *uc) {
	Timer * me = (Timer *)si->si_value.sival_ptr;
	me->timer_func(me->timer_func_param);
}

int Timer::create_timer_1(Timer_func func, void* p) {
	timer_func = func;
	timer_func_param = p;

	struct sigevent evp;
	memset(&evp, 0, sizeof(evp));

	evp.sigev_notify = SIGEV_THREAD;
	evp.sigev_value.sival_ptr = this;
	evp.sigev_notify_function = s_timer_thread;

	pthread_attr_t att;
	struct sched_param param;
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_attr_init(&att);
	pthread_attr_setschedpolicy(&att, SCHED_FIFO);
	pthread_attr_setschedparam(&att, &param);
	pthread_attr_setinheritsched(&att, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setdetachstate(&att, PTHREAD_CREATE_DETACHED);
	evp.sigev_notify_attributes = &att;
	pthread_attr_destroy(&att);

	if (timer_create(CLOCK_MONOTONIC, &evp, &timer_id) == -1) {
		perror("timer_create");
		return -1;
	}
	return 0;
}


int Timer::create_timer_3(int SIG, __pid_t tid, Timer_func func, void* p)
{
	timer_func = func;
	timer_func_param = p;

	struct sigevent sev;
	//sigset_t mask;
	struct sigaction sa;

	/* Establish handler for timer signal */
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = s_timer_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1)
		perror("sigaction");

	/* Create the timer */
	sev.sigev_notify = SIGEV_THREAD_ID;
	sev._sigev_un._tid = tid;//send signal to this thread
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = this;

	if (timer_create(CLOCK_MONOTONIC, &sev, &timer_id) == -1) {
		perror("timer_create");
		return -1;
	}
	return 0;
}


int Timer::timer_start(int flag, unsigned long period) {
	timer_set_expire(flag, period);
	clock_gettime(CLOCK_MONOTONIC, &now);
	next = now;
	next.tv_sec += interval.tv_sec;
	next.tv_nsec += interval.tv_nsec;
	tsnorm(&next);

	int timermode = 0;
	if (timermode == TIMER_ABSTIME)
		tspec.it_value = next;
	else {
		tspec.it_value = interval;
	}

	if (timer_settime(timer_id, timermode, &tspec, 0) == -1) {
		perror("timer_settime");
		return -1;
	}
	return 0;
}

/* init time expire :interval */
int Timer::timer_set_expire(int flag, unsigned long p)
{
	period = p;
	interval.tv_sec = period / USEC_PER_SEC;
	interval.tv_nsec = (period % USEC_PER_SEC) * 1000;

	if (flag == TIMER_EXPIRE_EACH) {
		tspec.it_value = interval;
		tspec.it_interval = interval;
	}
	else if (flag == TIMER_EXPIRE_ONCE) {
		tspec.it_value = interval;
		tspec.it_interval.tv_sec = 0;
		tspec.it_interval.tv_nsec = 0;
	}

	return 0;
}

int Timer::timer_stop() {
	struct itimerspec t;
	t.it_value.tv_sec = 0;
	t.it_value.tv_nsec = 0;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_nsec = 0;
	if (timer_settime(timer_id, 0, &t, 0) == -1) {
		perror("timer_settime");
		return -1;
	}
	return 0;
}

int Timer::delete_timer() {
	if (timer_delete(timer_id) == -1) {
		perror("timer_delete");
		return -1;
	}
	//LOG_D(g_logger, "delete_timer, name = " << name);
	return 0;
}

static inline void tsnorm(struct timespec *ts)
{
	while (ts->tv_nsec >= NSEC_PER_SEC) {
		ts->tv_nsec -= NSEC_PER_SEC;
		ts->tv_sec++;
	}
}

void Timer::time_cost_start(struct timespec *p) {
	clock_gettime(CLOCK_MONOTONIC, p);
}

// calculate the time last from the begining
int64_t Timer::time_cost_stop(struct timespec *p) {
	struct timespec start = *p;
	clock_gettime(CLOCK_MONOTONIC, p);
	return calc_time_diff_ns(start, *p);
}

//int64_t ensure return 64 bits, return ns
int64_t Timer::calc_time_diff_ns(struct timespec start, struct timespec end) {
	int64_t temp;
	temp = (end.tv_sec - start.tv_sec) * TIMER_NANO + end.tv_nsec
		- start.tv_nsec;
	return temp;
}
