#pragma once

#define COLOR_DEF "\033[1;32;40m"
#define COLOR_INFO "\033[1;32;44m"
#define COLOR_WARN "\033[1;33;40m"
#define COLOR_ERROR "\033[1;31;40m"

#define COLOR_PIPE "\033[1;32;44m"
#define COLOR_STATE "\033[1;32;44m"
#define COLOR_AB "\033[1;32;46m"

class Hub;
class ThreadSync;
class Logger;
class Console;

extern Hub g_hub;
extern ThreadSync g_threadsync;
extern std::string g_home_path;
extern Logger g_logger;
extern Logger g_log2file;
extern Console g_console;