#include <UnitTest++/UnitTest++.h>
#include "CalculatorRefactored.h"
#include "ConnectorRefactored.h"
#include "LoggerRefactored.h"
#include "ClientHandler.h"
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
        CHECK_THROW(conn.connect_to_registry(""), crit_err);
    }

    TEST(wrong_path) {
        ConnectorRefactored conn;
        CHECK_THROW(conn.connect_to_registry("invalid/path.txt"), crit_err);
    }

    TEST(correct_path) {
        ConnectorRefactored conn;
        CHECK_EQUAL(0, conn.connect_to_registry("/home/stud/kursach2/base/test_files/base.txt"));
    }
}

// Test for Logger
SUITE(Logger_test) {
    TEST(void_path_log) {
        Logger logger;
        CHECK_THROW(logger.set_path(""), std::invalid_argument);
    }

    TEST(wrong_path_log) {
        Logger logger;
        CHECK_THROW(logger.set_path("/non/existent/path/log.txt"), crit_err);
    }

    TEST(correct_path_log) {
        Logger logger;
        CHECK_EQUAL(0, logger.set_path("/home/stud/kursach2/base/test_files/log.txt"));
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

// Main entry for running all tests
int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    return UnitTest::RunAllTests();
}
