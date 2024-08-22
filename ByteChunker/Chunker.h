#pragma once

#include <stdint.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

/**
* @class Chunker
* @brief Класс для разбивки данных на порции и конвертации их в строки.
*/
class Chunker {
private:
	size_t lastChunkSize; ///< Размер последней порции

public:
	/**
	* @brief Конструктор по умолчанию.
	*/
	Chunker() : lastChunkSize(0) {}

	/**
	* @brief Рассчитывает размер идентификатора для каждой порции.
	* @param dataSize Размер исходных данных.
	* @param chunkSize Размер каждой порции.
	* @return Размер идентификатора в байтах.
	*/
	static size_t getIdSize(size_t dataSize, size_t chunkSize);

	/**
	* @brief Разбивает данные на порции.
	* @param data Указатель на исходные данные.
	* @param dataSize Размер исходных данных.
	* @param chunkSize Размер каждой порции.
	* @param chunkCount Переменная для хранения количества порций.
	* @return Двумерный массив с порциями данных.
	* @throw std::invalid_argument Если указатель на данные равен нулю или размер порции равен нулю.
	*/
	uint8_t** split(const uint8_t* data, size_t dataSize, size_t chunkSize, size_t& chunkCount);

	/**
	* @brief Конвертирует порции данных в строки.
	* @param chunks Двумерный массив с порциями данных.
	* @param chunkCount Количество порций.
	* @param chunkSize Размер каждой порции.
	* @param idSize Размер идентификатора в байтах.
	* @return Массив строк, содержащих данные порций в шестнадцатеричном формате.
	* @throw std::invalid_argument Если указатель на порции данных равен нулю.
	*/
	std::string* convertChunksToStrings(uint8_t** chunks, size_t chunkCount, size_t chunkSize, size_t idSize);

	/**
	* @brief Возвращает размер последней порции.
	* @return Размер последней порции.
	*/
	size_t getLastChunkSize() const;
};