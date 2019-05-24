#include<iostream>
#include"Global.h"
#include"Hub.h"
#include"Console.h"
#include"ThreadSync.h"
#include"Logger.h"

// 定义全局变量
const char* g_god = "ZhengGuozhen";
std::string g_home_path = "../";

Logger g_logger(LOGGER_CONSOLE_ASYNC);
//Logger g_logger;
Logger g_log2file(LOGGER_FILE_ASYNC);// here, will create file in g_home_path,
									 // if path not exist, this logger will not work
Hub g_hub;
Console g_console;
ThreadSync g_threadsync;