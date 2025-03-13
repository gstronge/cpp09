#include "../incl/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string inputFile) : _inputFile(inputFile) {}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseDatabase() {
	std::ifstream	file;
	file.open(_dataFile);

	if(!file.is_open())
	{
		std::cout << "Error: could not open file.\n";
		exit (EXIT_FAILURE);
	}

	std::string		buffer;
	size_t			pos;

	while (std::getline(file, buffer))
	{
		pos = buffer.find(",");
		if (pos != std::string::npos && !buffer.empty() && buffer != "date,exchange_rate")
			_dataMap[buffer.substr(0, pos)] = std::stof(buffer.substr(pos + 1));
	}
	file.close();
}


void BitcoinExchange::parseInput() {
	std::ifstream	file;
	file.open(this->_inputFile);

	if(!file.is_open())
	{
		std::cout << "Error: could not open file.\n";
		exit (EXIT_FAILURE);
	}

	std::string		buffer;
	size_t			pos;
	float			ex_rate;
	float			value;

	while (std::getline(file, buffer))
	{
		pos = buffer.find_first_not_of("0123456789-");
		if ((pos == std::string::npos || buffer.find(" | ") == std::string::npos) && !buffer.empty())
			std::cout << "Error: bad input => " << buffer << "\n";
		if (pos != std::string::npos && buffer != "date | value")
		{
			ex_rate = processDate(buffer.substr(0, pos));
			value = processValue(buffer.substr(pos + 3));
			if (ex_rate >= 0 && value >= 0)
				std::cout << buffer.substr(0, pos) << " => " << value << " = " << ex_rate * value << "\n";
		}		
	}
	file.close();
}

float	BitcoinExchange::processDate(const std::string date) {
	if (date.empty())
		return -1;
	return 0;
}

float	BitcoinExchange::processValue(const std::string value) {
	if (value.empty())
		return -1;
	return 0;
}


#include <iomanip>

// void BitcoinExchange::printMap() {
// 	auto	iter = _dataMap.begin();

// 	std::cout << "here\n";
// 	while (iter != _dataMap.end())
// 	{
// 		std::cout << "first: >" << iter->first << "< | " << "second: >" << std::fixed << std::setprecision(2) << iter->second << "<\n";
// 		iter++;
// 	}
// }

