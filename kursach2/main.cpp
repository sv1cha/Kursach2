#include <iostream>
#include "ConnectorRefactored.h"
#include "InterfaceRefactored.h"
#include "ClientHandler.h"
#include "CalculatorRefactored.h"
#include "LoggerRefactored.h"
#include "Errors.h"

int main(int argc, const char** argv)
{
    try {
    InterfaceRefactored ui;
    ui.process_command(argc, argv);
    } catch (crit_err& e) {
        std::cerr << "Critical error: " << e.what() << "\n";
    } catch (po::error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "Use -h for help\n";
    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception!\n";
    }
    return 0;
