/** @file
* @author Сверчков А.Д.
* @version 1.0
* @date 26.11.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#pragma once
#include <stdexcept>
#include <string>

/**
 * @brief Класс для обработки критических ошибок.
 */
class crit_err : public std::runtime_error {
public:
    /**
     * @brief Конструктор критической ошибки.
     *
     * @param message Сообщение об ошибке.
     */
    explicit crit_err(const std::string& message);
};

/**
 * @brief Класс для обработки некритических ошибок.
 */
class no_crit_err : public std::runtime_error {
public:
    /**
     * @brief Конструктор некритической ошибки.
     *
     * @param message Сообщение об ошибке.
     */
    explicit no_crit_err(const std::string& message);
};
