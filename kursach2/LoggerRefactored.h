#pragma once
#include <string>

class Logger
{
    static std::string get_current_datetime(std::string format);
    std::string log_file_path;
public:
    int writelog(std::string message);
    int set_path(std::string file_path);
    Logger() { log_file_path = " "; }
    Logger(std::string path) { log_file_path = path; }
};
