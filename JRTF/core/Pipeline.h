#pragma once
#include <stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<sys/syscall.h>
#include <unistd.h>

#include"Global.h"
#include"AB.h"
#include"Timer.h"
#include"ThreadObject.h"
#include"ThreadSync.h"

using namespace std;

class Pipeline
{
public:
	enum PIPE_MODE { ONCE, INTERVAL, INTERVAL_THREAD, EVENT, FAST, HOST };
	enum PIPE_STATE { PIPE_STATE_STOP, PIPE_STATE_TOSTOP, PIPE_STATE_IDLE, PIPE_STATE_RUN };

	Pipeline(string name, string mode);
	~Pipeline();

	void init();
	int add_ab(AB*);

	void set_period(unsigned long p) { period = p; }
	void set_policy(std::string p) { policy = p; }
	void set_priority(int p) { priority = p; }
	void set_affinity(unsigned long int p) { cpuset = p; }

	string get_name() { return my_name; }
	string set_name(string name) { my_name = name; return my_name; }
	vector<AB *>* get_all_ab() { return &ab_vector; }

	PIPE_MODE get_mode() { return my_mode; }
	PIPE_MODE set_mode(PIPE_MODE mode) { my_mode = mode; return my_mode; }
	
	PIPE_STATE get_state() { return my_state; }
	PIPE_STATE set_state(PIPE_STATE state) { my_state = state; return my_state; };

	//running functions
	void start();
	void stop() {
		set_state(PIPE_STATE_TOSTOP);
	}

	void run_once();
	void run_fast();
	void run_interval();
	void run_interval_thread();
	void run_event();
	void run_all_ab();
	static void *pipe_thread_func(void *pipeline);
	static void pipe_timer_func(void * p);

	ThreadSync threadsync;

private:
	static int pipe_num;
	string my_name;
	PIPE_STATE my_state;
	PIPE_MODE my_mode;
	__pid_t my_tid;
	uint64_t count_run;
	ThreadObject pipe_thread;
	Timer pipe_timer;
	int TIMER_SIG;
	std::string policy;
	int priority;
	unsigned long period; //us
	unsigned long int cpuset;
	vector<AB*> ab_vector;
};
