#include"TestFunc.h"

static int shutdown_main = 0;
static void sighand(int sig)
{
	shutdown_main = 1;
}

int main(int argc, char *argv[]) {
	//run_test();
	test_create_pipe_ab();
	g_console.start();
	/*
	* set logger
	*/
	g_logger.setLevel(log4cplus::ALL_LOG_LEVEL);
	//g_logger.setLevel(log4cplus::OFF_LOG_LEVEL);
	//Logger::delete_old(32); // delete by name!
	LOG4CPLUS_DEBUG(g_logger._logger, "logger is OK! " << &g_logger);
	// set signal handle
	signal(SIGINT, sighand);
	signal(SIGTERM, sighand);
	signal(SIGUSR1, sighand);
	while (!shutdown_main) {
		pause();
	}
}
