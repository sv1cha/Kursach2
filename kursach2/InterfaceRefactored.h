/** @file
* @author Сверчков А.Д.
* @version 1.0
* @date 26.11.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#pragma once
#include "LoggerRefactored.h"
#include <string>

/**
 * @brief Интерфейс для обработки командной строки.
 */
class InterfaceRefactored {
public:
    /// Конструктор по умолчанию.
    InterfaceRefactored(int argc, const char** argv);

    /**
     * @brief Обработка командной строки.
     *
     * @param argc Количество аргументов.
     * @param argv Аргументы командной строки.
     * @param is_test Режим тестирования.
     * 
     * @return Код успешного выполнения.
     */
     int process_command(int argc, const char** argv, bool is_test = false);
};
