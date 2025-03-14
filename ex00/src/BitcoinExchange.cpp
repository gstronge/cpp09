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
		{
						
			_dataMap[dateToInt(buffer)] = std::stof(buffer.substr(pos + 1));
		}
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
	float			ex_rate;
	float			value;

	while (std::getline(file, buffer))
	{
		if (inputIsValid(buffer))
		{
			ex_rate = processDate(dateToInt(buffer));
			value = std::stof(buffer.substr(13));
			if (buffer != "date | value")
				std::cout << buffer.substr(0, 10) << " => " << value << " = "<< std::fixed << std::setprecision(2) << ex_rate * value << "\n";
		}
		else if (buffer != "date | value")
			std::cout << _errorMsg << "\n";	
	}
	file.close();
}

float	BitcoinExchange::processDate(int inputDate) {
	auto	iter = _dataMap.begin();

	if (iter->first > inputDate)
		return (iter->second);

	iter = _dataMap.find(inputDate);
	if (iter != _dataMap.end())
		return (iter->second);
	
	while (iter == _dataMap.end())
	{
		inputDate--;
		iter = _dataMap.find(inputDate);
		if (iter != _dataMap.end())
			return (iter->second);
	}
	return 0;
}


bool	BitcoinExchange::inputIsValid(const std::string buffer) {
	if (buffer.empty())
	{
		_errorMsg = "Error: bad input => LINE IS EMPTY";
		return (false);
	}
	if (buffer.find(" | ") == std::string::npos || buffer.size() < 14)
	{
		_errorMsg = "Error: bad input => " + buffer;
		return (false);
	}

	std::string		date_str = buffer.substr(0, 10);
	std::string		num_str = buffer.substr(13);

	if (!dateIsValid(date_str))
	{
		_errorMsg = "Error: bad input => " + buffer;
		return (false);
	}
	if (std::stof(num_str) <= 0)
	{
		_errorMsg = "Error: not a positive number";
		return (false);
	}
	if (std::stof(num_str) > 1000)
	{
		_errorMsg = "Error: too large a number";
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::dateIsValid(const std::string dateStr) {
	int		year = std::stoi(dateStr.substr(0, 4));
	int		month = std::stoi(dateStr.substr(5, 2));
	int		day = std::stoi(dateStr.substr(8, 2));

	if (year < 2009 || month < 1 || month > 12 || day < 1)

	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (day > 31)
				return (false);
			break;
		case 4: case 6: case 9: case 11:
			if (day > 30)
				return (false);
			break;
		case 2:
			if ((year == 2012 || year == 2016 || year == 2020 || year == 2024) && month > 29)
				return (false);
			if (!(year == 2012 || year == 2016 || year == 2020 || year == 2024) && month > 28)
				return (false);
	}

	if (dateStr.find_first_not_of("0123456789-") != std::string::npos || dateStr[4] != '-' || dateStr[7] != '-')
		return (false);
	return (true);
}

int	BitcoinExchange::dateToInt(const std::string dateStr) {
	int		date;

	date = 10000 * std::stoi(dateStr.substr(0, 4));
	date += 100 * std::stoi(dateStr.substr(5, 2));
	date += std::stoi(dateStr.substr(8, 2));

	return (date);
}




// void BitcoinExchange::printMap() {
// 	auto	iter = _dataMap.begin();

// 	std::cout << "here\n";
// 	while (iter != _dataMap.end())
// 	{
// 		std::cout << "first: >" << iter->first << "< | " << "second: >" << std::fixed << std::setprecision(2) << iter->second << "<\n";
// 		iter++;
// 	}
// }

