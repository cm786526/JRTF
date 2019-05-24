#include"UdpHelper.h"
UdpHelper::UdpHelper() {
	localip = "127.0.0.1";
	localport = 11022;

	remoteip = "";
	remoteport = 11023;

	myaddrlen = sizeof(myaddr);            /* length of addresses */
	remaddrlen = sizeof(remaddr);

	recvlen = 0;
	fd = 0;

	memset(rbuf, 0, sizeof(rbuf));
	memset(sbuf, 0, sizeof(sbuf));

	message_process_func = NULL;
	message_process_func_param = NULL;

}

UdpHelper::~UdpHelper() {
	close(fd);
}

int UdpHelper::setLocalAddress(std::string p1, uint16_t p2) {
	localip = p1;
	localport = p2;

	/* create a UDP socket */
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
	}

	/* bind the socket to any valid IP address and a specific port */
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(localport);//htons(0) pick any port number
									   //myaddr.sin_addr.s_addr = htonl(INADDR_ANY); //this will use all 127...
	char *local = const_cast<char*>(localip.c_str());
	if (inet_aton(local, &myaddr.sin_addr) == 0) {
		fprintf(stderr, "inet_aton() failed\n");
	}

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
	}

	//		int nZero = 0;
	//		setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero));
	//		setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero));

	return 0;
}

int UdpHelper::setRemoteAddress(std::string p1, uint16_t p2) {
	remoteip = p1;
	remoteport = p2;

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */
	memset((char *)&remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(remoteport);
	char *remote = const_cast<char*>(remoteip.c_str());	/* change this to use a different server */
	if (inet_aton(remote, &remaddr.sin_addr) == 0) {
		fprintf(stderr, "inet_aton() failed\n");
	}

	return 0;
}

int UdpHelper::send(std::string m) {
	sprintf(sbuf, m.c_str());
	if (sendto(fd, sbuf, strlen(sbuf), 0, (struct sockaddr *)&remaddr, remaddrlen) == -1) {
		perror("sendto");
	}

	return 0;
}

int UdpHelper::send(std::string p1, uint16_t p2, std::string m) {
	setRemoteAddress(p1, p2);

	sprintf(sbuf, m.c_str());
	if (sendto(fd, sbuf, strlen(sbuf), 0, (struct sockaddr *)&remaddr, remaddrlen) == -1) {
		perror("sendto");
	}

	return 0;
}

void UdpHelper::receive(Message_handle_function func, void* func_param) {
	message_process_func = func;
	message_process_func_param = func_param;

	thread_udp_receive.set_name("thread_udp_receive");
	thread_udp_receive.set_policy_priority("other", 0);
	thread_udp_receive.set_detached();
	thread_udp_receive.thread_function = thread_udp_receive_func;
	thread_udp_receive.thread_function_param = this;
	thread_udp_receive.run();

}

void UdpHelper::receive_loop() {
	for (;;) {
		//printf("waiting on port %d\n", localport);
		recvlen = recvfrom(fd, rbuf, UDPHELPER_RBUF, 0, (struct sockaddr *)&(remaddr), &(remaddrlen));
		//printf("received %d bytes\n", recvlen);

		if (recvlen > 0 && recvlen < UDPHELPER_RBUF) {
			rbuf[recvlen] = 0;

			printf("UdpHelper received from %s:%d, \"%s\"\n", inet_ntoa(remaddr.sin_addr), ntohs(remaddr.sin_port), rbuf);

			std::string message(rbuf);

			message_process_func(message_process_func_param, message);

		}
		else {
			perror("receive");
		}

	}
	/* never exits */
}