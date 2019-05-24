#include"AB.h"

AB::AB() :my_state(AB_STATE_IDLE), my_name("no_name") 
{
	my_enable = true;
	count_run = 0;
	time_act = 0;
	time_min = 1000;
	time_max = 0;
	time_avg = 0;
}

AB::~AB()
{
}


