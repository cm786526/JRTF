#include "Ratio.h"

Ratio::Ratio()
{
	cmd_name = "ratio";
	base = 1;
}

Ratio::~Ratio()
{
}

void Ratio::invoke(double m_base)
{
	base = m_base;
}
