#pragma once
#include <stdexcept>
#include <string>

class crit_err : public std::runtime_error {
public:
    explicit crit_err(const std::string& message) 
        : std::runtime_error("Critical Error: " + message) {}
};
class no_crit_err : public std::runtime_error {
public:
    explicit no_crit_err(const std::string& message) 
        : std::runtime_error("Non-Critical Error: " + message) {}
};
