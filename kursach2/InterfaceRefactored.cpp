#include "InterfaceRefactored.h"
#include "ConnectorRefactored.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include "ClientHandler.h"
#include "LoggerRefactored.h"
#include "Errors.h"

namespace po = boost::program_options;

InterfaceRefactored::InterfaceRefactored(int argc, const char** argv) {
    process_command(argc, argv);
}

int InterfaceRefactored::process_command(int argc, const char** argv, bool is_test) {
    bool default_database = false;
    bool default_log = false;
    bool default_port = false;
    int port_value;
    std::string log_path;
    std::string database_path;

    po::options_description opts("Available options");
    opts.add_options()
        ("help,h", "Display help")
        ("database,d", po::value<std::string>()->default_value("/etc/vcalc.conf"), "Specify path to database file")
        ("log,l", po::value<std::string>()->default_value("/var/log/vcalc.log"), "Specify path to log file")
        ("port,p", po::value<int>(&port_value)->default_value(33333), "Specify server port");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << opts << "\n";
        return 0;
    }
try {
    database_path = vm["database"].as<std::string>();
    log_path = vm["log"].as<std::string>();
    port_value = vm["port"].as<int>();

    // Установка флагов значений по умолчанию
    if (database_path == "/etc/vcalc.conf;") {
        default_database = true;
    }
    if (log_path == "/var/log/vcalc.log") {
        default_log = true;
    }
    if (port_value == 33333) {
        default_port = true;
    }

    if (port_value < 1024 || port_value > 65535) {
        throw crit_err("Invalid port number");
    }

    if (default_database && default_log && default_port) {
        std::cout << "Server started with default settings. Use -h for assistance" << std::endl;
    }

    Logger log(log_path);
    log.writelog("Log path set to: " + log_path);
    log.writelog("Database path set to: " + database_path);
    log.writelog("Port set to: " + std::to_string(port_value));
    ConnectorRefactored conn;
    conn.connect_to_registry(log, database_path );
    log.writelog("Connected to database successfully!");
    if (!is_test) {
        log.writelog("Server operational");
        ClientHandler handler;
        handler.manage_connection(port_value, database_path.c_str(),  &log);
    } else {
        std::cout << "Test mode: Server execution bypassed.\n";
    }
} catch (crit_err& e) {
        std::cerr << "crit_err: " << e.what() << std::endl;} 
    return 0;
}
