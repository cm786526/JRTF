#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <pthread.h>
#include <sstream>

#include "Console.h"
#include "UdpHelper.h"


#define REMOTE_CONTROL_LOCAL_IP "127.0.0.1"
#define REMOTE_CONTROL_LOCAL_PORT 11022


class RemoteControl {
public:
	RemoteControl();
	~RemoteControl();

	void setAddress(std::string ip, uint16_t port);

	void start();

	static void message_handle(void* p, std::string m) {
		// int a = 0;
		// LOG_E(g_logger, &a);
		// int a, udp1 and udp2 invoke this, the &a are different
		// static int a, udp1 and udp2 invoke this, the &a are same

		RemoteControl* me = (RemoteControl*)p;

		std::string input = m;
		if (input.substr(0, 1) == "$") {
			int r = Console::CmdProc(input.substr(1));

			std::stringstream ss;
			ss << "cmd = \"" << input << "\" result = " << r;

			//send(REMOTE_IP, REMOTE_PORT, ss.str());
			me->udp.send(ss.str()); // send back

		}
		else if (input.substr(0, 6) == "super:") {

		}
	}

private:
	UdpHelper udp;
	std::string myip;
	uint16_t myport;
};