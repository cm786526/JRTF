#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "ShareData.h"
#include "ThreadSync.h"
#include "Global.h"
#include "Timer.h"


using namespace std;
class AB;

class AB
{
public:
	enum AB_STATE { AB_STATE_IDLE, AB_STATE_RUN };

	AB();
	~AB();
	virtual int init() { return 0; };
	virtual int init_after() { return 0; };

	string get_name() { return my_name; }
	string set_name(string name) { my_name = name; return my_name; }
	int64_t get_run_count() { return count_run; }
	AB_STATE get_state() { return my_state; }
	void set_state_idle() { my_state = AB_STATE_IDLE; }
	void set_state_run() { my_state = AB_STATE_RUN; }
	virtual Hub* get_hub() { return my_hub; }
	virtual void set_hub(Hub *hub) { my_hub = hub; }

	void enable() { my_enable = true; }
	void disable() { my_enable = false; }
	
	virtual ShareData* get_data(std::string name) { return nullptr; }
	virtual int set_data(std::string p1, std::string p2) {};

	virtual void dowork() {};
	virtual void dodowork(){
		if (!my_enable)
			return;
		Timer::time_cost_start(&ts);
		set_state_run();
		threadsync.mutexlock();
		dowork();
		count_run++;
		threadsync.mutexunlock();
		set_state_idle();

		time_act = Timer::time_cost_stop(&ts) / 1000;

		if (time_act < time_min)
			time_min = time_act;
		if (time_act > time_max)
			time_max = time_act;
		time_avg += time_act;
		//std::cout << count_run<< endl << time_min << endl << time_max;
	}

	virtual void reset() {};

	bool my_enable;
	AB_STATE my_state;
	string my_name;
	int64_t count_run;
	int64_t time_act;
	int64_t time_min;
	int64_t time_max;
	int64_t time_avg;
	timespec ts;	// get time for calculate

	ThreadSync threadsync;
	ShareData sdata;
	Hub* my_hub;
private:

};