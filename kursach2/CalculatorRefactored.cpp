#include "CalculatorRefactored.h"

MathEngine::MathEngine(std::vector<int64_t> data)
{
    try {
        computed_value = 0;
        for(auto num : data) {
            computed_value += num * num;
            if (computed_value > INT64_MAX / 2) {
                computed_value = INT64_MAX;
            } else if (computed_value < INT64_MIN / 2) {
                computed_value = INT64_MIN;
            }
        }
    } catch (boost::numeric::negative_overflow& e) {
        computed_value = std::numeric_limits<int64_t>::lowest();
    } catch (boost::numeric::positive_overflow& e) {
        computed_value = std::numeric_limits<int64_t>::max();
    }
}

int64_t MathEngine::retrieve_result() {
    return computed_value;
}
