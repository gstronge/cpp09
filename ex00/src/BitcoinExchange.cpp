#include "../incl/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string inputFile) : _inputFile(inputFile) {}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parse() {
	std::ifstream	file;
	file.open(this->_inputFile);

	if(!file.is_open())
	{
		std::cout << "Error: could not open file.\n";
		exit (EXIT_FAILURE);
	}

	std::string		buffer;
	size_t			pos;
	std::string		temp_map_str;

	while (std::getline(file, buffer))
	{
		pos = buffer.find_first_of(" \t|");
		if (pos == std::string::npos && !buffer.empty())
			_btxMap["Error: bad input => "] = buffer.substr(pos + 3);
		else if (!buffer.empty() && buffer != "date | value")
			_btxMap[buffer.substr(0, pos)] = buffer.substr(pos + 3);
	}
	file.close();
}


void BitcoinExchange::printMap() {
	auto	iter = _btxMap.begin();

	while (iter != _btxMap.end())
	{
		std::cout << "first: >" << iter->first << "< | " << "second: >" << iter->second << "<\n";
		iter++;
	}
}

