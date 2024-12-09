#include "Errors.h"

crit_err::crit_err(const std::string& message) : std::runtime_error(message) {}

no_crit_err::no_crit_err(const std::string& message) : std::runtime_error(message) {}
