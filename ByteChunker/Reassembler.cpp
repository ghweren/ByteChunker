#include "Reassembler.h"

size_t Reassembler::getId(const std::string& str, size_t idSize) {
	if (str.length() < idSize * 2) throw std::invalid_argument("String too short for ID size");

	size_t id = 0;
	for (size_t i = 0; i < idSize * 2; i += 2) {
		std::string byteString = str.substr(i, 2);
		try {
			id = (id << 8) | std::stoi(byteString, nullptr, 16);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("Invalid hexadecimal character in string");
		}
	}
	return id;
}

uint8_t* Reassembler::reassemble(std::string* strings, size_t numStrings, size_t chunkSize, size_t idSize) {
	if (!strings) throw std::invalid_argument("Null strings pointer");

	uint8_t* result = new uint8_t[numStrings * chunkSize];
	bool *idSeen = new bool[numStrings];
	for (int i = 0; i < numStrings; i++)
		idSeen[i] = false;

	size_t offset = 0;

	std::vector<std::pair<size_t, const std::string*>> indexedStrings(numStrings);
	for (size_t i = 0; i < numStrings; ++i) {
		size_t id = getId(strings[i], idSize);
		if (id >= numStrings) throw std::out_of_range("Invalid ID in string");
		if (idSeen[id]) throw std::runtime_error("Duplicate ID found in strings");
		idSeen[id] = true;
		indexedStrings[i] = std::make_pair(id, &strings[i]);
	}

	std::sort(indexedStrings.begin(), indexedStrings.end(),
		[](const std::pair<size_t, const std::string*>& a, const std::pair<size_t, const std::string*>& b) {
		return a.first < b.first;
	});

	for (size_t i = 0; i < numStrings; ++i) {
		if (!idSeen[i]) throw std::runtime_error("Missing ID in input strings");

		const std::string& chunkData = *(indexedStrings[i].second);
		for (size_t j = idSize * 2; j < chunkData.length(); j += 2) {
			try {
				result[offset++] = static_cast<uint8_t>(std::stoi(chunkData.substr(j, 2), nullptr, 16));
			}
			catch (const std::invalid_argument&) {
				delete[] result;
				throw std::invalid_argument("Invalid hexadecimal character in string");
			}
		}
	}

	return result;
}