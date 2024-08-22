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
* @brief ����� ��� ������ ������ �� ��������� ������.
*/
class Reassembler {
public:
	/**
	* @brief ��������� ������������� �� ������.
	* @param str ������, ���������� ������������� � ������ ������.
	* @param idSize ������ �������������� � ������.
	* @return ������������� � ���� ������ �����.
	* @throw std::invalid_argument ���� ������ ������� ������� ��� �������� ������������ ����������������� �������.
	*/
	static size_t getId(const std::string& str, size_t idSize);

	/**
	* @brief ������ ������ �� ��������� ������.
	* @param strings ������ ����� � �������� ������.
	* @param numStrings ���������� ����� (������).
	* @param chunkSize ������ ������ ������.
	* @param idSize ������ �������������� � ������.
	* @return ��������� �� ��������� ������ ������.
	* @throw std::invalid_argument ���� ��������� �� ������ ����� ���� ��� ������ �������� ������������ �������.
	* @throw std::out_of_range ���� ������������� ������ ������� �� ���������� �������.
	* @throw std::runtime_error ���� ������ �������� ��� ����������� �������������.
	*/
	uint8_t* reassemble(std::string* strings, size_t numStrings, size_t chunkSize, size_t idSize);
};