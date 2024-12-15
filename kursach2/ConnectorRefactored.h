/** @file
* @author Сверчков А.Д.
* @version 1.0
* @date 26.11.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#pragma once
#include "LoggerRefactored.h"
#include <map>
#include <string>

/**
 * @brief Класс для подключения к реестру.
 */
class ConnectorRefactored
{
private:
    /// Реестр пользователей.
    std::map<std::string, std::string> registry;
public:

    /**
     * @brief Подключиться к реестру по заданному пути.
     *
     * @param path Путь к файлу реестра.
     * 
     * @return Код результата операции.
     */
    int connect_to_registry(Logger &log, std::string path = "/var/log/vcalc.log" );

    /**
     * @brief Получить реестр пользователей.
     *
     * @return Реестр в виде карты.
     */
    std::map<std::string, std::string> get_registry();
};
