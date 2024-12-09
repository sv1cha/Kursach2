#include <iostream>
#include "ConnectorRefactored.h"
#include "InterfaceRefactored.h"
#include "ClientHandler.h"
#include "CalculatorRefactored.h"
#include "LoggerRefactored.h"
#include "Errors.h"
#include <boost/program_options.hpp>

int main(int argc, const char** argv)
{
    InterfaceRefactored ui(argc, argv);
  return 0;
}

   
