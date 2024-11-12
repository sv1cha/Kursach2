#pragma once
#include <vector>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

class MathEngine
{
    int64_t computed_value;
public:
    MathEngine(std::vector<int64_t> data);
    int64_t retrieve_result();
};
