#include "Chunker.h"

size_t Chunker::getIdSize(size_t dataSize, size_t chunkSize) {
	size_t maxChunks = (dataSize + chunkSize - 1) / chunkSize;
	size_t idSize = 0;

	while (maxChunks > 0) {
		maxChunks >>= 8;
		idSize++;
	}

	return idSize;
}

uint8_t** Chunker::split(const uint8_t* data, size_t dataSize, size_t chunkSize, size_t& chunkCount) {
	if (!data) throw std::invalid_argument("Null data pointer");
	if (chunkSize == 0) throw std::invalid_argument("Chunk size cannot be zero");

	size_t idSize = getIdSize(dataSize, chunkSize);
	chunkCount = (dataSize + chunkSize - 1) / chunkSize;
	uint8_t** chunks = new uint8_t*[chunkCount];

	for (size_t i = 0; i < chunkCount; ++i) {
		size_t currentChunkSize = std::min(chunkSize, dataSize - i * chunkSize);
		if (i == chunkCount - 1) {
			lastChunkSize = currentChunkSize;
		}
		chunks[i] = new uint8_t[idSize + currentChunkSize];


		for (size_t j = 0; j < idSize; ++j) {
			chunks[i][j] = (i >> ((idSize - 1 - j) * 8)) & 0xFF;
		}


		std::memcpy(chunks[i] + idSize, data + i * chunkSize, currentChunkSize);
	}

	return chunks;
}

std::string* Chunker::convertChunksToStrings(uint8_t** chunks, size_t chunkCount, size_t chunkSize, size_t idSize) {
	if (!chunks) throw std::invalid_argument("Null chunks pointer");

	std::string* strings = new std::string[chunkCount];

	for (size_t i = 0; i < chunkCount; ++i) {
		std::stringstream ss;
		size_t currentChunkSize = (i == chunkCount - 1) ? lastChunkSize : chunkSize;
		for (size_t j = 0; j < idSize + currentChunkSize; ++j) {
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(chunks[i][j]);
		}
		strings[i] = ss.str();
	}

	return strings;
}
