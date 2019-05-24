#pragma once
#include "AB.h"
#include "Hub.h"
#include "Ratio.h"

class TestInput : public AB
{
public:
	TestInput();
	~TestInput();
	int init();
	void dowork();
private:
	float* NI_6363_ai;
	AB* NI_6363_ao;
	double base;
	Cmd * cmd_ratio;
	bool test_trigger;
};
