#include"Hub.h"

Hub::Hub()
{
}

Hub::~Hub()
{
}

// add the cmd pointer to the map

int Hub::add_cmd(Cmd * cmd)
{
	string cmd_name = cmd->get_name();

	if (cmd_map.find(cmd_name) != cmd_map.end()) {
		std::cout << "ERROR, HUB::addcmd, name conflict, cmd_name = " << cmd_name << std::endl;
		exit(0);
	}
	cmd_map.insert(std::make_pair(cmd_name, cmd));
}

// get the Cmd according to the name

Cmd * Hub::get_cmd(string cmd_name)
{
	map<std::string, Cmd*>::iterator it = cmd_map.find(cmd_name);
	if (it != cmd_map.end())
		return cmd_map[cmd_name];
	else {
		std::cout << COLOR_ERROR << "Hub getAB error, name = " << cmd_name << COLOR_DEF << std::endl;
		return NULL;
	}
}

//add the pipeline pointer to the map.
int Hub::add_pipe(Pipeline *p) {
	string pipe_name = p->get_name();

	if (pipe_map.find(pipe_name) != pipe_map.end()) {
		std::cout << "ERROR, HUB::addpipe, name conflict, pipe_name = " << pipe_name << std::endl;
		exit(0);
	}


	pipe_map.insert(std::make_pair(pipe_name, p));

	vector<AB *> *ab_vector = p->get_all_ab();
	for (vector<AB *>::iterator iter = ab_vector->begin(); iter != ab_vector->end(); iter++) {
		string ab_name = (*iter)->get_name();
		string pipe_ab_name = pipe_name + ":" + ab_name;

		// ab_name must be unique
		if (ab_map.find(ab_name) != ab_map.end()) {
			std::cout << "ERROR, HUB::addpipe, name conflict, ab_name = " << ab_name << std::endl;
			exit(0);
		}


		pipe_ab_map[pipe_ab_name] = (*iter);
		ab_map[ab_name] = (*iter);
	}

	return 0;
}


AB* Hub::get_ab(string ab) {
	map<std::string, AB*>::iterator it = ab_map.find(ab);
	if (it != ab_map.end())
		return ab_map[ab];
	else {
		std::cout << COLOR_ERROR << "Hub getAB error, name = " << ab << COLOR_DEF << std::endl;
		return NULL;
	}
}

Pipeline* Hub::get_pipe(string pipe) {
	map<std::string, Pipeline*>::iterator it = pipe_map.find(pipe);
	if (it != pipe_map.end())
		return pipe_map[pipe];
	else {
		std::cout << COLOR_ERROR << "Hub getPipe error, name = " << pipe << COLOR_DEF << std::endl;
		return NULL;
	}
}

ShareData* Hub::get_data_from_other_ab(std::string pipe_ab_name, std::string name)
{
	if (pipe_ab_map.find(pipe_ab_name) != pipe_ab_map.end())
	{
		AB* the_ab = pipe_ab_map[pipe_ab_name];
		return the_ab->get_data(name);
	}
	else
	{
		std::cout << "this pipe does not have the ab" << endl;
		return new ShareData(TYPE_NONE);
	}
}
