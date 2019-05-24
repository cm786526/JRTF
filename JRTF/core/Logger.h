#pragma once

#include <iostream>
#include <dirent.h>
#include <sys/syscall.h>
#include <signal.h>
#include <sstream>
#include <pthread.h>
#include <semaphore.h>
#include"Global.h"
#include"ThreadObject.h"
#include"ThreadSync.h"


#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/layout.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/fileappender.h"

#include "log4cplus/config.hxx"
#include "log4cplus/streams.h"
#include "log4cplus/logger.h"
#include "log4cplus/helpers/snprintf.h"
#include "log4cplus/tracelogger.h"

#define LOG_D(logger,p) \
		{\
		LOG4CPLUS_DEBUG((logger)._logger, p);\
		}
#define LOG_I(logger,p) \
		{\
		LOG4CPLUS_INFO((logger)._logger, COLOR_INFO<<p<<COLOR_DEF);\
		}
#define LOG_W(logger,p) \
		{\
		LOG4CPLUS_WARN((logger)._logger, COLOR_WARN<<p<<COLOR_DEF);\
		}
#define LOG_E(logger,p) \
		{\
		LOG4CPLUS_ERROR((logger)._logger, COLOR_ERROR<<p<<COLOR_DEF);\
		}

#define LOG_ASYNC(logger,p) \
		{\
		(logger).ts.mutexlock(); \
		(logger).ss_log<<"<ZGZG<"<<p<<">ZGZG>"; \
		(logger).ts.sempost();\
		(logger).ts.mutexunlock();\
		}

#define LOGGER_CONSOLE 1
#define LOGGER_FILE 2
#define LOGGER_CONSOLE_ASYNC 3
#define LOGGER_FILE_ASYNC 4

class Logger
{
public:
	Logger();
	Logger(std::string file);
	Logger(int mode);
	Logger(int mode, std::string file);
	~Logger();

	void init_console();
	void init_file(std::string file);


	void set_file(std::string file);

	static void* log_thread(void *);
	static void sig_handler(int sig, siginfo_t *si, void *uc);
	void send_singal(void * p) {
		sigval sv;
		//sv.sival_ptr=const_cast<char*>(input.c_str());
		sv.sival_ptr = p;
		sigqueue(mytid, SIGUSR1, sv);
	}

	void setLevel(int log_level);

	static void delete_old(int max_file_num);

	template<class out_type, class in_value>
	static out_type convert(const in_value & t) {
		std::stringstream stream;
		stream << t;
		out_type result;
		stream >> result;
		return result;
	}

	log4cplus::Logger _logger;
	__pid_t mytid;
	std::stringstream ss_log;//all log write in it
	ThreadSync ts;

private:
	static int num;
	ThreadObject mythread;
};