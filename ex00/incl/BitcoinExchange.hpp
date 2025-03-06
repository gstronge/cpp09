#pragma once

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
private:
	std::string							_inputFile;
	std::map<std::string, std::string>	_btxMap;

public:
	BitcoinExchange(const std::string inputFile);
	// BitcoinExchange(BitcoinExchange& other);
	~BitcoinExchange();

	void parse();

	// BitcoinExchange&	operator=(BitcoinExchange& other);

	void	printMap();
};