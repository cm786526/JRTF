#include <iostream>
#include "Global.h"
#include "Hub.h"
#include "Pipeline.h"
#include "TestInput.h"
#include "Console.h"
#include "AbNiAi.h"
#include "AbNiAo.h"
#include "Logger.h"
#include "Rfm.h"


static std::vector<Pipeline *> pipe_vector;
static std::vector<AB *> ab_vector;

void run_test();

vector<Pipeline *> test_create_pipe_ab();