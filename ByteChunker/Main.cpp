/**
* @file main.cpp
* @brief Программа для разделения массива данных на порции, конвертации их в строки и последующей сборки.
*
* Эта программа разбивает данные на порции фиксированного размера, добавляет к каждой порции уникальный
* идентификатор, конвертирует порции в строки, перемешивает их и затем собирает данные обратно в исходный массив.
*/

#include <iostream>
#include "Chunker.h"
#include "Reassembler.h"
#include <random>
#include <chrono>


/**
* @brief Выводит массив байт в шестнадцатеричном формате.
* @param array Указатель на массив байт.
* @param size Размер массива.
* @param printSize Количество байт для вывода (по умолчанию 20).
*/
void printArray(const uint8_t* array, size_t size, size_t printSize = 20){
	for (size_t i = 0; i < std::min(size, printSize); ++i) {
		std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(array[i]) << " ";
	}
	if (size > printSize) {
		std::cout << "... ";
	}
	std::cout << std::endl;
}

/**
* @brief Главная функция программы.
*
* В этой функции создается массив данных, который затем разбивается на порции. Каждая порция конвертируется в строку.
* Строки перемешиваются, а затем собираются обратно в исходный массив. Проверяется эквивалентность исходных и
* собранных данных, выводятся результаты теста.
*
* @return Код завершения программы.
*/
int main(){
	const size_t dataSize = 10000;
	size_t chunkSize = 3;
	size_t chunkCount;


	std::vector<uint8_t> data(dataSize);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 255);

	for (size_t i = 0; i < dataSize; ++i) {
		data[i] = static_cast<uint8_t>(dis(gen));
	}

	Chunker chunker;


	auto start = std::chrono::high_resolution_clock::now();
	uint8_t** chunks = chunker.split(data.data(), dataSize, chunkSize, chunkCount);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Splitting time: " << duration.count() << " seconds." << std::endl;

	size_t idSize = Chunker::getIdSize(dataSize, chunkSize);


	start = std::chrono::high_resolution_clock::now();
	std::string* strings = chunker.convertChunksToStrings(chunks, chunkCount, chunkSize, idSize);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Conversion to strings time: " << duration.count() << " seconds." << std::endl;


	start = std::chrono::high_resolution_clock::now();
	std::random_shuffle(strings, strings + chunkCount);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Shuffling time: " << duration.count() << " seconds." << std::endl;

	Reassembler reassembler;


	start = std::chrono::high_resolution_clock::now();
	uint8_t* reassembledData = reassembler.reassemble(strings, chunkCount, chunkSize, idSize);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Reassembling time: " << duration.count() << " seconds." << std::endl;

	bool areEqual = (std::memcmp(data.data(), reassembledData, dataSize) == 0);

	if (areEqual) {
		std::cout << "The original data and the reassembled data are equal." << std::endl;
	}
	else {
		std::cout << "The original data and the reassembled data are NOT equal." << std::endl;
		std::cout << "Original data (first 20 bytes): ";
		printArray(data.data(), dataSize);
		std::cout << "Reassembled data (first 20 bytes): ";
		printArray(reassembledData, dataSize);

		std::cout << "Original data (last 20 bytes): ";
		printArray(data.data() + dataSize - 20, 20);
		std::cout << "Reassembled data (last 20 bytes): ";
		printArray(reassembledData + dataSize - 20, 20);
	}

	for (size_t i = 0; i < chunkCount; ++i) {
		delete[] chunks[i];
	}
	delete[] chunks;
	delete[] strings;
	delete[] reassembledData;

	system("pause");
	return 0;
}