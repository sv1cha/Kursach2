#include <iostream>
#include <fstream>
#include "Errors.h"
#include "LoggerRefactored.h"
#include "ConnectorRefactored.h"

using namespace std;

int ConnectorRefactored::connect_to_registry(string path) {
    if (path.find('.') == std::string::npos) {
        throw crit_err("File name missing extension");
    }
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        throw crit_err("Cannot open file " + path);
    }
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            string username = line.substr(0, pos);
            string password = line.substr(pos + 1);
            if (!username.empty() && !password.empty()) {
                registry[username] = password;
            }
        }
    }
    
    Logger log;
    log.set_path("/var/log/vcalc.log");
    
    if (registry.empty()) {
        log.writelog("Database is empty or contains missing credentials");
        throw crit_err("Database is empty or contains invalid data");
    }
    return 0;
}
