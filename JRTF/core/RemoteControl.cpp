#include"RemoteControl.h"

RemoteControl::RemoteControl() {
	myip = REMOTE_CONTROL_LOCAL_IP;
	myport = REMOTE_CONTROL_LOCAL_PORT;

}
RemoteControl::~RemoteControl() {

}

void RemoteControl::setAddress(std::string ip, uint16_t port) {
	myip = ip;
	myport = port;
}

void RemoteControl::start() {
	udp.setLocalAddress(myip, myport);
	udp.receive(message_handle, this);
}