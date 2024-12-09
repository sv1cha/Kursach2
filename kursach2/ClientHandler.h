#pragma once
#include <string>
#include <map>
#include "LoggerRefactored.h"
#include "Errors.h"

/**
 * @brief Класс для управления соединениями клиентов.
 */
class ClientHandler
{
public:

    /**
     * @brief Управление соединениями на заданном порту.
     * 
     * @param port Порт сервера для прослушивания.
     * @param registry_path Путь к файлу реестра клиентов.
     * @param log_path Путь к файлу логов.
     * @param logger Указатель на объект логгера.
     * 
     * @return Код результата операции.
     */
    int manage_connection(int port, const char* registry_path,  Logger* logger);

    /**
     * @brief Создать соль для хеширования.
     *
     * @return Сгенерированная строка соли.
     */
    static std::string create_salt();

    /**
     * @brief Вычислить MD5 хеш от строки.
     *
     * @param input Строка для хеширования.
     * 
     * @return Хешированная строка.
     */
    static std::string compute_md5(const std::string& input);
};
