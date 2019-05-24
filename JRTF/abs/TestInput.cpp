#include"TestInput.h"
TestInput::TestInput()
{
	base = 0;
	test_trigger = false;
}

TestInput::~TestInput()
{

}

int TestInput::init()
{
	cmd_ratio = g_hub.get_cmd("ratio");
	NI_6363_ao = g_hub.get_ab("ao");
	return 1;
}
void TestInput::dowork()
{
	// get ratio base
	if (get_run_count() < 5005) {
		if (cmd_ratio)
			base = cmd_ratio->get_data();

		ShareData * temp = g_hub.get_data_from_other_ab("pipe_io:ai", "all");
		if (temp->share != nullptr)
		{
			NI_6363_ai = temp->convert_data_array<float>();
			if (get_run_count() == 5000)
				test_trigger = true;
			if (NI_6363_ao) {
				if (test_trigger)
					NI_6363_ao->set_data("channel", to_string(0));
				else
				{
					NI_6363_ao->set_data("channel", to_string(NI_6363_ai[2] * base));
					//NI_6363_ao->set_data("channel", to_string(3 * base));
				}

			}
			//cout <<"***get=***" << NI_6363_ai[0] << endl;
			delete temp->share;
		}
	}
	else
	{
		exit(0);
	}

}
