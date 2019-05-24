#pragma once
#include <iostream>
#include <sstream>
#include <string.h>
#include <bitset>
#include "Global.h"
#include "Hub.h"
#include "AB.h"
#include "ThreadObject.h"
#include "Cmd.h"

class Console {
public:
	Console();
	~Console();
	int start();
	static int CmdProc(std::string);		//�������������
	static void* console_thread(void *);
private:
	ThreadObject mythread;
};