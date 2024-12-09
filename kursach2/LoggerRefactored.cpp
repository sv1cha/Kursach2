#include "LoggerRefactored.h"
#include "Errors.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Logger::Logger() : log_file_path("") {}

Logger::Logger(std::string path) {
    set_path(path);
}

int Logger::set_path(std::string file_path) {
    if (file_path.empty() || file_path.find('.') == std::string::npos) {
        throw crit_err("Invalid log file path");
    }
    std::ofstream log_file(file_path, std::ios_base::out | std::ios_base::app);
    // Проверяем, можно ли открыть файл по первоначальному пути
    if (!log_file.is_open()) {
        std::cerr << "Ошибка: не удалось создать лог в " << file_path
                  << ". Переход в резервный путь /tmp/log/vcalc.log" << std::endl;
        file_path = "/tmp/log/vcalc.log";  // Указываем резервный путь
        log_file.open(file_path, std::ios_base::out | std::ios_base::app);
        // Если резервный путь также не удается открыть, бросаем исключение
        if (!log_file.is_open()) {
            throw crit_err("Не удалось создать лог-файл: " + file_path);
        }
    }
    log_file.close();  // Закрываем файл после проверки его открытия
    log_file_path = file_path;  // Обновляем путь лог-файла
    return 0;
}

std::string Logger::get_current_datetime(std::string format) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    if (format == "now") {
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    } else if (format == "date") {
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    }
    return ss.str();
}

int Logger::writelog(std::string message) {
    if (log_file_path.empty()) {
        throw crit_err("Log file path not set");
    }

    std::ofstream log_file(log_file_path, std::ios_base::out | std::ios_base::app);
    if (!log_file.is_open()) {
        throw crit_err("Cannot open log file at path: " + log_file_path);
    }

    std::string time = get_current_datetime("now");
    log_file << time << " " << message << std::endl;
    log_file.close();
    if (!log_file) {
        throw crit_err("Failed to write to log file");
    }
    return 0;
}
