#pragma once

#include "AB.h"
#include "Cmd.h"

class Ratio: public Cmd
{
public:
	Ratio();
	~Ratio();
	void invoke(double m_base);
	double set_base(double m_base) { base = m_base; return base; }
	double get_data() {return base; }
private:
	double base;
};
