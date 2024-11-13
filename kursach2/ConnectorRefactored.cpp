#include <iostream>
#include <fstream>
#include "Errors.h"
#include "LoggerRefactored.h"
#include "ConnectorRefactored.h"

using namespace std;

int ConnectorRefactored::connect_to_registry(string path)
{
    if (path.find('.') == std::string::npos) {
        throw crit_err("File name missing extension");
    }
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        throw crit_err("Cannot open file " + path);
    }
    string line;
    string password;
    string username;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            username = line.substr(0, pos);
            password = line.substr(pos + 1);
            registry[username] = password;
        }
    }
    if (registry.empty()) {
        throw crit_err("File is empty or contains invalid data");
    }
    return 0;
}
