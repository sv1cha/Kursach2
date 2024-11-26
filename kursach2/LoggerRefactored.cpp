#include "LoggerRefactored.h"
#include <chrono>
#include <fstream>
#include "Errors.h"

using namespace std;

int Logger::set_path(std::string file_path)
{
    if (file_path.find('.') == std::string::npos) throw std::invalid_argument("File has no extension");
    std::ofstream log_file;
    log_file.open(file_path, std::ios_base::out | std::ios_base::app);
    if (!log_file.is_open()) {
        throw crit_err("Non-existent log path");
    }
    return 0;
}

string Logger::get_current_datetime(string format)
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    if (format == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (format == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return string(buf);
}

int Logger::writelog(std::string message)
{
    std::ofstream log_file;
    log_file.open(log_file_path, std::ios_base::out | std::ios_base::app);
    if (!log_file.is_open()) {
        throw crit_err("Non-existent log path");
    }
    std::string time = get_current_datetime("now");
    log_file << time << ' ' << message << std::endl;
    return 0;
}
