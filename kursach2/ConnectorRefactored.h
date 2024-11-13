#pragma once
#include <map>
#include <string>

class ConnectorRefactored
{
private:
    std::map<std::string, std::string> registry;
public:
    int connect_to_registry(std::string path = "/home/stud/kursach2/base/base.txt");
    std::map<std::string, std::string> get_registry()
    {
        return registry;
    }
};
