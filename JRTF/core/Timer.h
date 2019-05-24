#pragma once
#include <stdio.h>
#include<iostream>
#include<signal.h>
#include<cstring>
#include <sys/time.h>

using namespace std;

#define TIMER_EXPIRE_EACH 0
#define TIMER_EXPIRE_ONCE 1
#define USEC_PER_SEC		1000000
#define NSEC_PER_SEC		1000000000
const int64_t TIMER_NANO = 1000000000;


typedef void(*Timer_func_thread)(union sigval sig_val);
typedef void(*Timer_func_handler)(int sig, siginfo_t *si, void *uc);
typedef void(*Timer_func)(void *);

class Timer
{
public:
	Timer();
	~Timer();

	int timer_start(int flag, unsigned long period);
	int timer_stop();
	int create_timer_1(Timer_func func, void* p);
	int create_timer_3(int SIG, __pid_t tid, Timer_func func, void* p);
	static void s_timer_thread(union sigval sig_val);
	static void s_timer_handler(int sig, siginfo_t *si, void *uc);

	int delete_timer();
	int timer_set_expire(int flag, unsigned long p);

	static int64_t calc_time_diff_ns(struct timespec start, struct timespec end);
	static void time_cost_start(struct timespec *p);
	static int64_t time_cost_stop(struct timespec *p);

	string timer_name;
	timer_t timer_id;
	Timer_func timer_func;
	void * timer_func_param;
	unsigned long period; //us

	struct timespec now, next, interval, stop;
	struct itimerval itimer;
	struct itimerspec tspec;
private:

};

