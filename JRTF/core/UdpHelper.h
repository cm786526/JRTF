#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <pthread.h>
#include <sstream>

#include "ThreadObject.h"
#include "Logger.h"
#include "Global.h"


#define UDPHELPER_RBUF 1024
#define UDPHELPER_SBUF 1024

typedef void(*Message_handle_function)(void* p, std::string m);

class UdpHelper {
public:
	UdpHelper();

	~UdpHelper();

	int setLocalAddress(std::string p1, uint16_t p2);

	int setRemoteAddress(std::string p1, uint16_t p2);

	int send(std::string m);

	int send(std::string p1, uint16_t p2, std::string m);

	void receive(Message_handle_function func, void* func_param);

	void receive_loop();

	static void* thread_udp_receive_func(void* p) {
		UdpHelper* me = (UdpHelper*)p;

		int policy = 0;
		struct sched_param param;
		pthread_getschedparam(pthread_self(), &policy, &param);
		LOG_D(g_logger,
			"Thread start, " << "thread_udp_receive" << " pid=" << getpid()
			<< " tid=" << syscall(SYS_gettid) << " policy=" << policy << " priority=" << param.__sched_priority << std::endl
			<< "Receiving, my address = " << me->localip << ":" << me->localport);
		me->receive_loop();
		return NULL;
	}

private:

	std::string localip;
	uint16_t localport;

	std::string remoteip;
	uint16_t remoteport;

	struct sockaddr_in myaddr;      /* our address */
	struct sockaddr_in remaddr;     /* remote address */
	socklen_t myaddrlen;            /* length of addresses */
	socklen_t remaddrlen;

	int recvlen;                    /* # bytes received */
	int fd;                         /* our socket */
	char rbuf[UDPHELPER_RBUF];     /* receive buffer */
	char sbuf[UDPHELPER_SBUF];     /* receive buffer */

	ThreadObject thread_udp_receive;
	Message_handle_function message_process_func;
	void* message_process_func_param;

};