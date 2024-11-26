#include "CalculatorRefactored.h"

MathEngine::MathEngine(std::vector<int64_t> data) {
    computed_value = 0;
    for (auto num : data) {
        int64_t square;
        
        // Check for potential overflow
        if (num > 0 && num > (INT64_MAX - computed_value) / num) {
            computed_value = INT64_MAX;
            return;
        } else if (num < 0 && num < (INT64_MIN - computed_value) / num) {
            computed_value = INT64_MIN;
            return;
        }

        // Safe to calculate
        square = num * num;
        computed_value += square;
    }
}

int64_t MathEngine::retrieve_result() {
    return computed_value;
}
