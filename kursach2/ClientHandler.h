#pragma once
#include <string>
#include <map>
#include "LoggerRefactored.h"
#include "Errors.h"

class ClientHandler
{
public:
    int manage_connection(int port, const char* registry_path, const char* log_path, Logger* logger);
    static std::string create_salt();
    static std::string compute_md5(const std::string& input);
};
