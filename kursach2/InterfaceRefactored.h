#pragma once
#include "LoggerRefactored.h"
#include <string>

class InterfaceRefactored
{
    int port_value;
public:
    InterfaceRefactored() {}
    int process_command(int argc, const char** argv);
};
