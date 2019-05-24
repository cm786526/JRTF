#include "Console.h"

Console::Console() {

}

Console::~Console() {

}


void* Console::console_thread(void* p) {
	Console * me = (Console*)p;
	ThreadObject::set_it_name("jrtf_console");
	int policy = 0;
	struct sched_param param;
	pthread_getschedparam(pthread_self(), &policy, &param);
	/*LOG_D(g_logger,
		"Thread start, " << me->mythread.get_name() << " pid=" << getpid()
		<< " tid=" << syscall(SYS_gettid) << " policy=" << policy << " priority=" << param.__sched_priority);*/


	usleep(300000);
	printf("\nCommand Line Console:\n$ ");
	for (;;) {

		std::string input;
		getline(std::cin, input);
		if (input == "") {
			std::cerr << "$ ";
			usleep(10000);
			continue;
		}
		//old method
		me->CmdProc(input);
		usleep(100000);
		std::cout << "\n$ ";

		/*
		//another method, send a signal to AB
		Hub myhub;
		AB* consoleAB = myhub.getAB("ABproc");
		__pid_t mytid = consoleAB->mypipe->getTid();
		int console_SIG = SIGUSR1;//console SIG is different from TIMER_SIG

		sigval sv;
		sv.sival_ptr=const_cast<char*>(input.c_str());
		sigqueue(mytid,console_SIG,sv);

		continue;
		*/
	}

	return NULL;
}

int Console::start() {
	mythread.set_name("thread_console");
	mythread.set_policy_priority("other", 0);
	mythread.set_detached();
	mythread.thread_function = console_thread;
	mythread.thread_function_param = this;
	mythread.run();
	return 0;
}


/*
名称：		s_CmdProc
功能：		处理输入命令
返回值：	0, -1
*/
int Console::CmdProc(std::string input) {

	std::string p1 = "";
	std::string p2 = "";
	std::string temp = "";
	std::stringstream ss(input);
	ss >> p1;
	ss >> p2;
	//p2 includes the all rest characters
	while (ss >> temp) {
		p2 += " " + temp;
	}

	Cmd * cmd = g_hub.get_cmd(p1);
	if (cmd)
	{
		cmd->invoke(atof(p2.c_str()));
		std::cout << "successfully execute the command" << std::endl;
	}

	if (p1 == "who") {
		std::cout << "Hello, I am JRTF, can I help you?" << std::endl;

	}
	else if (p1 == "exit") {
		exit(0);
	}
	else if (p1 == "sh") {
		//g_hub.printState();

	}
	else if (p1 == "ss") {
		//g_hub.printStatistics();

	}
	else if (p1 == "err") {
		std::cout << COLOR_ERROR;
	}
	else if (p1 == "to") {
		std::cout << "Set pipe timeout " << p2 << std::endl;
		//Pipeline::PIPE_TIMEOUT_JUDGE = atof(p2.c_str());

	}
	else if (p1 == "log") {
		if (p2 == "0") {
			//g_logger.setLevel(log4cplus::OFF_LOG_LEVEL);
			std::cout << "g_logger.setLevel(log4cplus::OFF_LOG_LEVEL);" << std::endl;
		}
		else if (p2 == "1") {
			//g_logger.setLevel(log4cplus::ALL_LOG_LEVEL);
			std::cout << "g_logger.setLevel(log4cplus::ALL_LOG_LEVEL);" << std::endl;
		}

	}
	else if (p1 == "io") {
		if (g_hub.get_ab("ABai") == NULL || g_hub.get_ab("ABdio") == NULL || g_hub.get_ab("ABproc") == NULL) {
			std::cout << COLOR_ERROR;
			std::cout << "Error, can't find ABai or ABdio or ABproc" << std::endl;
			std::cout << COLOR_DEF;
			std::cerr << std::endl << "$ ";
			return -1;
		}

		/*float NI_6363_ai[32];
		g_hub.get_ab("ABai")->safe_get_data("NI_6363_ai", &NI_6363_ai);
		float NI_6363_ao[4];
		g_hub.get_ab("ABproc")->safe_get_data("NI_6363_ao", &NI_6363_ao);
		unsigned int NI_6363_dio;
		g_hub.get_ab("ABdio")->safe_get_data("NI_6363_dio", &NI_6363_dio);
		std::bitset<32> bbb = NI_6363_dio;
		unsigned int NI_6363_dio_2;
		g_hub.get_ab("ABdio")->safe_get_data("NI_6363_dio_2", &NI_6363_dio_2);
		std::bitset<32> bbb2 = NI_6363_dio_2;

		std::stringstream ss;
		for (int i = 0; i<32; i++) {
			ss << " ai" << i << "=" << NI_6363_ai[i] << " ";
			if (i % 8 == 7)
				ss << std::endl;
		}
		std::cout << ss.str() << std::endl;

		ss.clear();
		ss.str("");
		for (int i = 0; i<4; i++) {
			ss << " ao" << i << "=" << NI_6363_ao[i] << " ";
		}
		std::cout << ss.str() << std::endl << std::endl;

		std::cout << " channel(*10) " << "33222222222211111111110000000000" << std::endl
			<< " channel(*01) " << "10987654321098765432109876543210" << std::endl
			<< "  dio value = " << bbb
			<< std::endl;
		std::cout << " channel(*10)     " << "33222222222211111111110000000000" << std::endl
			<< " channel(*01)     " << "10987654321098765432109876543210" << std::endl
			<< "  dio_pfi value = " << bbb2
			<< std::endl;*/

	}
	else if (p1 == "tm") {
		std::stringstream ss(p2);
		std::string name;
		unsigned long period;
		ss >> name;
		ss >> period;

		if (g_hub.get_pipe(name) == NULL) {
			std::cout << COLOR_ERROR;
			std::cout << "Error, can't find Pipe! name = " << p2 << std::endl;
			std::cout << COLOR_DEF;

			std::cerr << std::endl << "$ ";
			return -1;
		}

		Pipeline* thePipe = g_hub.get_pipe(name);

		if (thePipe->get_mode() != Pipeline::INTERVAL) {
			std::cout << "Can't set the time, the mode of pipe is not ITVAL!" << std::endl;
		}
		else {
			thePipe->set_period(period);
			/*thePipe->get_timer().timer_start(TIMER_EXPIRE_EACH, period);
			std::cout << "Set period, " << "pipe=" << thePipe->get_name() << " period=" << period << std::endl;*/
		}

	}
	else if (p1 == "ab") {
		std::stringstream ss(p2);
		std::string name;
		std::string param1;
		std::string param2;
		std::string temp;
		ss >> name;
		ss >> param1;
		ss >> param2;
		while (ss >> temp) {
			param2 += " " + temp;
		}


		if (g_hub.get_ab(name) == NULL) {
			std::cout << COLOR_ERROR;
			std::cout << "Error, can't find AB! name = " << name << std::endl;
			std::cout << COLOR_DEF;

			std::cerr << std::endl << "$ ";
			return -1;
		}
		//AB* theAB = g_hub.get_ab(name);

		//theAB->threadsync.mutexlock();
		//theAB->set_data(param1, param2);
		//theAB->threadsync.mutexunlock();

		//		std::cout<<"AB::set_data()"
		//				<<" AB="<<theAB->getName()
		//				<<" param1="<<param1
		//				<<" param2="<<param2
		//				<<std::endl;

	}
	else if (p1 == "usleep") {
		std::stringstream ss(p2);
		int temp = 0;
		ss >> temp;
		usleep(temp);
	}
	else if (p1 == "res") {
		//g_hub.reset_all_ab();
	}
	/*else {
		std::cout << "Usage:\n"
			<< " who: Say hello\n"
			<< " sh: Print state of Pipes and ABs\n"
			<< " ss: Start statistics of Pipes, include histogram\n"
			<< " to <factor>: Set pipe timeout factor\n"
			<< " log <param>: Set log stwitch, 0=disable all, 1=enable console, 11=enable console and file\n"
			<< " io: Show the value of NI Pxie 6363\n"
			<< " tm <name> <period>: Set the period of a Pipe\n"
			<< " ab <name> <param1> <param2>: Invoke set_data method of a AB, include mutex\n"
			<< " err: change color\n"
			<< " usleep: usleep (us)\n"
			<< " res: reset all AB\n"
			<< std::endl;
	}*/

	return 0;

}

