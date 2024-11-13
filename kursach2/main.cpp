#include <iostream>
#include "ConnectorRefactored.h"
#include "InterfaceRefactored.h"
#include "ClientHandler.h"
#include "CalculatorRefactored.h"
#include "LoggerRefactored.h"
#include "Errors.h"

int main(int argc, const char** argv)
{
    InterfaceRefactored ui;
    ui.process_command(argc, argv);
    return 0;
}
