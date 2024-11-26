/** @file
* @author Сверчков А.Д.
* @version 1.0
* @date 26.11.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#pragma once
#include <vector>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

/**
 * @brief Класс для математических вычислений.
 */
class MathEngine
{
    /// Значение, вычисляемое с помощью методов класса.
    int64_t computed_value;
public:

    /**
     * @brief Конструктор, вычисляющий сумму квадратов элементов.
     *
     * @param data Вектор целых чисел для обработки.
     */
    MathEngine(std::vector<int64_t> data);

    /**
     * @brief Получить вычисленное значение.
     *
     * @return Вычисленное значение.
     */
    int64_t retrieve_result();
};
