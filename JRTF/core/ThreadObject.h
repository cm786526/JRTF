#pragma once
#include <stdio.h>
#include<iostream>
#include<string>
#include<pthread.h>
#include<sys/prctl.h>


typedef void * (*ThreadObject_function)(void *); //pointer point to a function

using namespace std;
class ThreadObject
{
public:
	ThreadObject();
	~ThreadObject();

	void run();
	void join();
	
	void set_name(string name) { my_name = name; }
	string get_name() { return my_name; }


	void set_policy_priority(std::string policy, int priority);
	void set_contention_scope(int Scope);
	void set_detached(void);
	void set_joinable(void);
	void set_affinity(unsigned long int cpuset);
	int name2policy(string polname);
	string policy2name(int policy);
	static void set_it_name(std::string name);

	string my_name;
	pthread_t my_tid;
	pthread_attr_t sched_attr;

	ThreadObject_function thread_function;
	void * thread_function_param;

private:

};
