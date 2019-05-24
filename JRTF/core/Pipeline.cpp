#include"Pipeline.h"

int Pipeline::pipe_num = 0;
Pipeline::Pipeline(string name, string mode)
{
	pipe_num++;
	if (pipe_num>16) {
		std::cout << "Error, pipe number must less than 16." << std::endl;
		exit(0);
	}
	my_name = name;
	if (mode == "once")
		my_mode = ONCE;
	else if (mode == "fast")
		my_mode = FAST;
	else if (mode == "interval")
		my_mode = INTERVAL;
	else if (mode == "event")
		my_mode = EVENT;
	else
	{
		my_mode = FAST;
		std::cout << COLOR_ERROR
			<< "Wrong, the mode is not supported, set mode to default value (FAST)."
			<< COLOR_DEF
			<< std::endl;
	}
	init();
}

Pipeline::~Pipeline()
{
}

void Pipeline:: init() {
	my_state = PIPE_STATE_IDLE;
	count_run = 0;
	TIMER_SIG = SIGRTMIN + pipe_num;
}

int Pipeline::add_ab(AB* ab) {
	ab_vector.push_back(ab);
	return 0;
}

void Pipeline::start() {
	pipe_thread.set_name("thread_" + get_name());
	pipe_thread.set_policy_priority(policy, priority);
	pipe_thread.set_affinity(cpuset);
	pipe_thread.set_detached();
	pipe_thread.thread_function = pipe_thread_func;
	pipe_thread.thread_function_param = this;
	pipe_thread.run();
}

//thread function cann't be a inner function
void* Pipeline::pipe_thread_func(void *pipeline) {
	Pipeline * me = (Pipeline *)pipeline;
	me->my_tid = syscall(SYS_gettid);//save the pipe thread tid to mytid

	ThreadObject::set_it_name("jrtf_" + me->get_name());

	g_threadsync.mutexlock();
	//ThreadObject::print_it_info(me->pipe_thread.get_name());
	g_threadsync.mutexunlock();
	me->threadsync.condwait();
	me->set_state(PIPE_STATE_RUN);
	switch (me->my_mode) {
	case ONCE:
		me->run_once();
		break;

	case FAST:
		me->run_fast();
		break;

	case INTERVAL:
		me->run_interval();
		break;

	case INTERVAL_THREAD:
		me->run_interval_thread();
		break;

	case EVENT:
		me->run_event();
		break;

	default:
		break;
	}

	me->set_state(PIPE_STATE_STOP);
	return NULL;
}

void Pipeline::run_once() {

	run_all_ab();
}

void Pipeline::run_fast() {

}

void Pipeline::run_interval() {
	pipe_timer.create_timer_3(TIMER_SIG, syscall(SYS_gettid), pipe_timer_func, (void *)this);
	pipe_timer.timer_start(TIMER_EXPIRE_EACH, period);
	while (my_state != PIPE_STATE_TOSTOP) {
		pause();	 //wait for signal
	}
	pipe_timer.delete_timer();
}

void Pipeline::run_event() {

}

void Pipeline::run_interval_thread() {

}

void Pipeline::run_all_ab() {
	for (std::vector<AB *>::iterator iter = ab_vector.begin(); iter != ab_vector.end(); ++iter) {
		(*iter)->dodowork();
	}
}


void Pipeline::pipe_timer_func(void * p)
{

	Pipeline * me = (Pipeline*)p;
	//jitter_warn only used in interval mode
	//me->jitter_check(PIPE_TIMEOUT_JUDGE);
	me->run_all_ab();
	return;
}