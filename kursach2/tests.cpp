#include <UnitTest++/UnitTest++.h>
#include "CalculatorRefactored.h"
#include "ConnectorRefactored.h"
#include "LoggerRefactored.h"
#include "ClientHandler.h"
#include "InterfaceRefactored.h"
#include <chrono>
#include <thread>

// Test for MathEngine (CalculatorRefactored)
SUITE(MathEngine_test) {
    TEST(positive_overflow) {
        std::vector<int64_t> data = {INT64_MAX / 2 + 1, INT64_MAX / 2 + 1};
        MathEngine calc(data);
        CHECK_EQUAL(INT64_MAX, calc.retrieve_result());
    }
    
    TEST(negative_overflow) {
        std::vector<int64_t> data = {-INT64_MAX / 2 - 1, -INT64_MAX / 2 - 1};
        MathEngine calc(data);
        CHECK_EQUAL(INT64_MIN, calc.retrieve_result());
    }
}

// Test for ConnectorRefactored
SUITE(ConnectorRefactored_test) {
    TEST(void_path) {
        ConnectorRefactored conn;
        Logger logger;
        CHECK_THROW(conn.connect_to_registry(logger, ""), crit_err);
    }

    TEST(wrong_path) {
        ConnectorRefactored conn;
        Logger logger;
        CHECK_THROW(conn.connect_to_registry(logger, "invalid/path.txt"), crit_err);
    }

    TEST(correct_path) {
        ConnectorRefactored conn;
        Logger logger;
        CHECK_EQUAL(0, conn.connect_to_registry(logger, "/etc/vcalc.conf"));
    }
}

// Test for Logger
SUITE(Logger_test) {
    TEST(void_path_log) {
        Logger logger;
        CHECK_THROW(logger.set_path(""), crit_err);
    }

    SUITE(Logger_test) {
    TEST(wrong_path_log_fallback) {
        Logger logger;
        CHECK_EQUAL(0, logger.set_path("/non/existent/path/log.txt")); // Проверяем успешный переход
    }
}
    TEST(correct_path_log) {
        Logger logger;
        CHECK_EQUAL(0, logger.set_path("/home/stud/kursach2/base/log.txt"));
    }
}

// Test for ClientHandler (Salt and MD5)
SUITE(ClientHandler_test) {
    TEST(salt_generator) {
        std::string salt1 = ClientHandler::create_salt();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::string salt2 = ClientHandler::create_salt();
        CHECK(salt1 != salt2);
    }

    TEST(md5_generation) {
        std::string test_input = "test_input";
        std::string hash1 = ClientHandler::compute_md5(test_input);
        std::string hash2 = ClientHandler::compute_md5(test_input);
        CHECK_EQUAL(hash1, hash2);
    }
}

/**Test for InterfaceRefactored
SUITE(InterfaceRefactored_test) {
    TEST(default_options) {
        const char* argv[] = {"program"};
        InterfaceRefactored interface(1, argv);
        CHECK_EQUAL(0, interface.process_command(1, argv, true));
    }

    TEST(custom_database_path) {
        const char* argv[] = {"program", "--database", "/home/stud/kursach2/base/base.txt"};
        InterfaceRefactored interface(3, argv);
        CHECK_EQUAL(0, interface.process_command(3, argv, true));
    }

    TEST(invalid_port) {
        const char* argv[] = {"program", "--port", "70000"};
        InterfaceRefactored interface(3, argv);
        CHECK_THROW(interface.process_command(3, argv, true), crit_err);
    }
}
*/
// Main entry for running all tests
int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    return UnitTest::RunAllTests();
}
