#pragma once
#include "iostream"
using namespace std;

class Cmd
{
public:
	Cmd();
	~Cmd();
	virtual void invoke(double m_base) = 0;
	string get_name() { return cmd_name; }
	virtual double get_data(){};
protected:
	string cmd_name;
};