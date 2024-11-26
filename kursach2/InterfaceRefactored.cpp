#include "InterfaceRefactored.h"
#include "ConnectorRefactored.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "ClientHandler.h"
#include "LoggerRefactored.h"
#include "Errors.h"

namespace po = boost::program_options;

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
        ("database,d",
         po::value<std::string>()->default_value("/home/stud/kursach2/base/base.txt"),
         "Specify path to database file")
        ("log,l",
         po::value<std::string>()->default_value("/home/stud/kursach2/base/log.txt"),
         "Specify path to log file")
        ("port,p",
         po::value<int>(&port_value)->default_value(33333),
         "Specify server port");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, opts), vm);
        po::notify(vm);
        if (vm.count("help")) {
            std::cout << opts << "\n";
            exit(0);
        }

        if (vm.count("database")) {
            if (vm["database"].as<std::string>() == "/home/stud/kursach2/base/base.txt") {
                default_database = true;
            }
            database_path = vm["database"].as<std::string>();
        }
        if (vm.count("log")) {
            if (vm["log"].as<std::string>() == "/home/stud/kursach2/base/log.txt") {
                default_log = true;
            }
            log_path = vm["log"].as<std::string>();
        }

        if (vm.count("port")) {
            if (vm["port"].as<int>() == 33333) {
                default_port = true;
            }
            port_value = vm["port"].as<int>();
            std::cout << "1" << std::endl;
        }

        if (port_value < 1024 || port_value > 65535) {
            throw crit_err("Invalid port number");
        }
        if (default_database && default_log && default_port) {
            std::cout << "Server started with default settings. Use -h for assistance" << std::endl;
        }

        Logger log(log_path);
        if (log_path != "/home/stud/kursach2/base/log.txt") {
            log.writelog("Log path set to: " + log_path);
        } else {
            log.writelog("Log path uses default setting");
        }
        if (database_path != "/home/stud/kursach2/base/base.txt") {
            log.writelog("Database path set to: " + database_path);
        } else {
            log.writelog("Database path uses default setting");
        }
        if (port_value != 33333) {
            log.writelog("Port set to custom value");
        } else {
            log.writelog("Port uses default setting");
        }
        
        ConnectorRefactored conn;
        conn.connect_to_registry(database_path);
        log.writelog("Connected to database successfully!");

        if (!is_test) {
            log.writelog("Server operational");
            ClientHandler handler;
            handler.manage_connection(port_value, database_path.c_str(), log_path.c_str(), &log);
        } else {
            std::cout << "Test mode: Server execution bypassed.\n";
        }
    return 0;
}
