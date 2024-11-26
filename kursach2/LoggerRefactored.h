/** @file
* @author Сверчков А.Д.
* @version 1.0
* @date 26.11.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#pragma once
#include <string>

/**
 * @brief Класс для записи логов.
 */
class Logger
{
    /**
     * @brief Получить текущую дату и время.
     *
     * @param format Формат вывода.
     * 
     * @return Строка с текущей датой и временем.
     */
    static std::string get_current_datetime(std::string format);

    /// Путь к файлу логов.
    std::string log_file_path;

public:

    /**
     * @brief Записать сообщение в лог.
     *
     * @param message Сообщение для записи.
     * 
     * @return Код успешной записи.
     */
    int writelog(std::string message);

    /**
     * @brief Установить путь к файлу логов.
     *
     * @param file_path Новый путь к файлу логов.
     * 
     * @return Код успешного выполнения.
     */
    int set_path(std::string file_path);

    /// Конструктор по умолчанию.
    Logger();
    
    /**
     * @brief Конструктор с указанием пути.
     *
     * @param path Путь к файлу логов.
     */
    Logger(std::string path);
};
