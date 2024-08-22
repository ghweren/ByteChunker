#pragma once

#include <stdint.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
//#include <utility>
#include <vector>

/**
* @class Reassembler
* @brief Класс для сборки данных из строковых порций.
*/
class Reassembler {
public:
	/**
	* @brief Извлекает идентификатор из строки.
	* @param str Строка, содержащая идентификатор и данные порции.
	* @param idSize Размер идентификатора в байтах.
	* @return Идентификатор в виде целого числа.
	* @throw std::invalid_argument Если строка слишком коротка или содержит недопустимые шестнадцатеричные символы.
	*/
	static size_t getId(const std::string& str, size_t idSize);

	/**
	* @brief Сборка данных из строковых порций.
	* @param strings Массив строк с порциями данных.
	* @param numStrings Количество строк (порций).
	* @param chunkSize Размер каждой порции.
	* @param idSize Размер идентификатора в байтах.
	* @return Указатель на собранный массив данных.
	* @throw std::invalid_argument Если указатель на строки равен нулю или строки содержат недопустимые символы.
	* @throw std::out_of_range Если идентификатор строки выходит за допустимые границы.
	* @throw std::runtime_error Если найден дубликат или отсутствует идентификатор.
	*/
	uint8_t* reassemble(std::string* strings, size_t numStrings, size_t chunkSize, size_t idSize);
};