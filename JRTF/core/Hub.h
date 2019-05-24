#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>

#include "AB.h"
#include "Pipeline.h"
#include "Ratio.h"

using namespace std;
class Hub
{
public:
	Hub();
	~Hub();
	int add_cmd(Cmd *);
	Cmd * get_cmd(string cmd_name);
	int add_pipe(Pipeline *p);
	AB * get_ab(string ab);
	Pipeline * get_pipe(string pipe);
	ShareData* get_data_from_other_ab(std::string ab_name, std::string name);

private:
	map<string, AB*> ab_map;
	map<string, Pipeline*> pipe_map;
	map<std::string, AB*> pipe_ab_map;
	map<string, Cmd *> cmd_map;
};