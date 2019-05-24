
#include "Logger.h"

#define LOG_SVAL_LIMIT 1024
#define LOG_SLENGTH_LIMIT 1024000 // 1mb

int Logger::num = 0;

Logger::Logger() {
	init_console();
}

Logger::Logger(std::string file) {
	init_file(file);
}

Logger::Logger(int mode)
{

	if (mode == LOGGER_CONSOLE_ASYNC) {
		init_console();
		mythread.set_name("thread_log2console_async");
		mythread.set_policy_priority("other", 0);
		mythread.set_detached();
		mythread.thread_function = log_thread;
		mythread.thread_function_param = this;
		mythread.run();
	}
	else if (mode == LOGGER_FILE_ASYNC) {
		init_file("");
		mythread.set_name("thread_log2file_async");
		mythread.set_policy_priority("other", 0);
		mythread.set_detached();
		mythread.thread_function = log_thread;
		mythread.thread_function_param = this;
		mythread.run();
	}
	else {
		std::cout << "Init Logger failed!" << std::endl;
		exit(0);
	}
}

Logger::Logger(int mode, std::string file)
{

	if (mode == LOGGER_FILE_ASYNC) {
		init_file(file);
		mythread.set_name("thread_log2file_async");
		mythread.set_policy_priority("other", 0);
		mythread.set_detached();
		mythread.thread_function = log_thread;
		mythread.thread_function_param = this;
		mythread.run();
	}
	else {
		std::cout << "Init Logger failed!" << std::endl;
		exit(0);
	}
}

Logger::~Logger()
{

}

void Logger::init_console() {

	/* step 1: Instantiate an appender object */
	log4cplus::helpers::SharedObjectPtr<log4cplus::Appender> _append(new log4cplus::ConsoleAppender());
	_append->setName("append for console");
	/* step 2: Instantiate a layout object */
	//std::string pattern = "%D{%Y/%m/%d %H:%M:%S:%Q}  - %m [%l]%n";
	std::string pattern = "%D{%Y/%m/%d %H:%M:%S:%Q}  - %m%n";
	std::auto_ptr<log4cplus::Layout> _layout(new log4cplus::PatternLayout(pattern));
	/* step 3: Attach the layout object to the appender */
	_append->setLayout(_layout);
	/* step 4: Instantiate a logger object */
	_logger = log4cplus::Logger::getInstance("log2console");
	/* step 5: Attach the appender object to the logger  */
	_logger.removeAllAppenders();//remove old appenders, or there will be many appenders!!!
	_logger.addAppender(_append);
	/* step 6: Set a priority for the logger  */
	_logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);
}

void Logger::init_file(std::string file) {

	std::string filename = "";
	if (file == "") {
		//set the log file name according the time
		time_t t = time(0);
		char tmp[128];
		strftime(tmp, sizeof(tmp), "%Y%m%d_%H%M%S", localtime(&t));//log file name and path
		filename = g_home_path + "/log/" + tmp + ".log";
	}
	else {
		filename = g_home_path + "/log/" + file;
	}

	/* step 1: Instantiate an appender object */
	log4cplus::SharedAppenderPtr _append(new log4cplus::FileAppender(filename));
	_append->setName("append for file");
	/* step 2: Instantiate a layout object */
	std::string pattern = "%m%n";
	//std::string pattern = pattern0;
	std::auto_ptr<log4cplus::Layout> _layout(new log4cplus::PatternLayout(pattern));
	/* step 3: Attach the layout object to the appender */
	_append->setLayout(_layout);
	/* step 4: Instantiate a logger object */
	_logger = log4cplus::Logger::getInstance("log2file");
	/* step 5: Attach the appender object to the logger  */
	_logger.removeAllAppenders();//remove old appenders, or there will be many appenders!!!
	_logger.addAppender(_append);
	/* step 6: Set a priority for the logger  */
	_logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);
	//	_logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
	//	_logger.setLogLevel(log4cplus::OFF_LOG_LEVEL);

}


void Logger::set_file(std::string file) {
	_logger.removeAllAppenders();
	std::string filename = g_home_path + "/log/" + file;
	log4cplus::SharedAppenderPtr _append(new log4cplus::FileAppender(filename));
	_append->setName("append for file");
	std::string pattern = "%m%n";
	std::auto_ptr<log4cplus::Layout> _layout(new log4cplus::PatternLayout(pattern));
	_append->setLayout(_layout);
	_logger.addAppender(_append);
}

void* Logger::log_thread(void* p) {
	ThreadObject::set_it_name("jrtf_logger");
	Logger* me = (Logger*)p;
	me->mytid = syscall(SYS_gettid);
	usleep(100);

	int policy = 0;
	struct sched_param param;
	pthread_getschedparam(pthread_self(), &policy, &param);
	std::cout <<
		"Thread start, " << me->mythread.get_name() << " pid=" << getpid()
		<< " tid=" << syscall(SYS_gettid) << " policy=" << policy << " priority=" << param.__sched_priority
		<< std::endl;

	std::string s = "";
	std::string::size_type position = 0;
	std::string temp = "";

	int sval = 0;

	while (true) {
		//pause();//wait for signal
		me->ts.semwait();//wait for sem_post
		me->ts.mutexlock();
		s = me->ss_log.str();
		me->ss_log.clear();
		me->ss_log.str("");
		sem_getvalue(&me->ts.sem, &sval);
		//std::cout<<sval<<std::endl;
		//std::cout<<s.length()<<std::endl;

		if (sval>LOG_SVAL_LIMIT || s.length()>LOG_SLENGTH_LIMIT) {
			std::cout << "ERROR, Logger is too busy, disable logger." << std::endl;
			std::cout << "sval = " << sval << " s.length() = " << s.length() << std::endl;

			me->setLevel(log4cplus::OFF_LOG_LEVEL);
			s = "";
		}
		if (sval>0) {
			if (sem_init(&me->ts.sem, 0, 0) != 0)
				perror("Semaphore initialization failed");
		}
		me->ts.mutexunlock();

		position = 0;//!!!must has this line!!!
		while (true)
		{
			position = s.find("<ZGZG<", position);
			if (position == std::string::npos)
				break;

			temp = s.substr(position + 6, s.find(">ZGZG>", position) - position - 6);
			position++;
			if (temp.length() != 0) {
				LOG4CPLUS_DEBUG(me->_logger, temp);
			}
		}
	}
	return NULL;
}


void Logger::setLevel(int log_level)
{
	/*

	* The <code>OFF_LOG_LEVEL</code> LogLevel is used during configuration to
	* turn off logging.
	const LogLevel OFF_LOG_LEVEL     = 60000;

	* The <code>FATAL_LOG_LEVEL</code> LogLevel designates very severe error
	* events that will presumably lead the application to abort.
	const LogLevel FATAL_LOG_LEVEL   = 50000;

	* The <code>ERROR_LOG_LEVEL</code> LogLevel designates error events that
	* might still allow the application to continue running.
	const LogLevel ERROR_LOG_LEVEL   = 40000;

	* The <code>WARN_LOG_LEVEL</code> LogLevel designates potentially harmful
	* situations.
	const LogLevel WARN_LOG_LEVEL    = 30000;

	* The <code>INFO_LOG_LEVEL</code> LogLevel designates informational
	* messages  that highlight the progress of the application at
	* coarse-grained  level.
	const LogLevel INFO_LOG_LEVEL    = 20000;

	* The <code>DEBUG_LOG_LEVEL</code> LogLevel designates fine-grained
	* informational events that are most useful to debug an application.
	const LogLevel DEBUG_LOG_LEVEL   = 10000;

	* The <code>TRACE_LOG_LEVEL</code> LogLevel is used to "trace" entry
	* and exiting of methods.
	const LogLevel TRACE_LOG_LEVEL   = 0;

	* The <code>ALL_LOG_LEVEL</code> LogLevel is used during configuration to
	* turn on all logging.
	const LogLevel ALL_LOG_LEVEL     = TRACE_LOG_LEVEL;

	* The <code>NOT_SET_LOG_LEVEL</code> LogLevel is used to indicated that
	* no particular LogLevel is desired and that the default should be used.

	const LogLevel NOT_SET_LOG_LEVEL = -1;

	*/
	if (log_level != -1 && log_level != 0 && log_level != 10000 && log_level != 20000 && log_level != 30000 && log_level != 40000 && log_level != 50000 && log_level != 60000)
	{
		std::cout << "Parameter error, log level should be -1 0 10000 20000 30000 40000 50000 60000." << std::endl;
		return;
	}

	_logger.setLogLevel(log_level);
	std::cout << "Logger, set log level to " << log_level << std::endl;

}

void Logger::sig_handler(int sig, siginfo_t *si, void *uc)
{
	//std::string log = (char*)si->si_value.sival_ptr;
	Logger* me = (Logger*)si->si_value.sival_ptr;
	std::string s;
}

void Logger::delete_old(int max_file_num) {
	std::string path = g_home_path + "/log/";
	std::vector<std::string> logfiles;

	DIR *dirp;
	struct dirent *direntp;
	dirp = opendir(path.c_str());

	//查找log目录下所有.log文件，存入vector
	if (dirp != NULL)
	{
		while (1)
		{
			direntp = readdir(dirp);
			if (direntp == NULL)
				break;
			else if (direntp->d_name[0] != '.') {
				std::string dname = direntp->d_name;

				if (dname.find(".") != std::string::npos) {
					if (dname.substr(dname.find(".")) == ".log") {
						//std::cout<<dname<<std::endl;
						logfiles.push_back(dname);
					}
				}
			}
		}
		closedir(dirp);
	}

	sort(logfiles.begin(), logfiles.end());

	//打印排序后vector信息
	//	std::cout<<"size = "<<logfiles.size()<<std::endl;
	//	for(std::vector<std::string>::iterator it = logfiles.begin(); it != logfiles.end(); it++){
	//		std::cout<<*it<<std::endl;
	//	}

	//如果log文件数量超过限制，删除老文件
	int n = logfiles.size();
	for (std::vector<std::string>::iterator it = logfiles.begin(); n > max_file_num; it++) {
		std::string dd = path + *it;
		remove(dd.c_str());
		n--;
	}

}