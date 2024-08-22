#pragma once

#include <stdint.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

/**
* @class Chunker
* @brief ����� ��� �������� ������ �� ������ � ����������� �� � ������.
*/
class Chunker {
private:
	size_t lastChunkSize; ///< ������ ��������� ������

public:
	/**
	* @brief ����������� �� ���������.
	*/
	Chunker() : lastChunkSize(0) {}

	/**
	* @brief ������������ ������ �������������� ��� ������ ������.
	* @param dataSize ������ �������� ������.
	* @param chunkSize ������ ������ ������.
	* @return ������ �������������� � ������.
	*/
	static size_t getIdSize(size_t dataSize, size_t chunkSize);

	/**
	* @brief ��������� ������ �� ������.
	* @param data ��������� �� �������� ������.
	* @param dataSize ������ �������� ������.
	* @param chunkSize ������ ������ ������.
	* @param chunkCount ���������� ��� �������� ���������� ������.
	* @return ��������� ������ � �������� ������.
	* @throw std::invalid_argument ���� ��������� �� ������ ����� ���� ��� ������ ������ ����� ����.
	*/
	uint8_t** split(const uint8_t* data, size_t dataSize, size_t chunkSize, size_t& chunkCount);

	/**
	* @brief ������������ ������ ������ � ������.
	* @param chunks ��������� ������ � �������� ������.
	* @param chunkCount ���������� ������.
	* @param chunkSize ������ ������ ������.
	* @param idSize ������ �������������� � ������.
	* @return ������ �����, ���������� ������ ������ � ����������������� �������.
	* @throw std::invalid_argument ���� ��������� �� ������ ������ ����� ����.
	*/
	std::string* convertChunksToStrings(uint8_t** chunks, size_t chunkCount, size_t chunkSize, size_t idSize);

	/**
	* @brief ���������� ������ ��������� ������.
	* @return ������ ��������� ������.
	*/
	size_t getLastChunkSize() const;
};