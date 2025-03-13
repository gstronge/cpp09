#pragma once

#include <iostream>
#include <fstream>
#include <map>



class BitcoinExchange
{
private:
	const std::string								_inputFile;
	const std::string								_dataFile = "data.csv";
	std::map<std::string, float>					_dataMap;

public:
	BitcoinExchange(const std::string inputFile);
	// BitcoinExchange(BitcoinExchange& other);
	~BitcoinExchange();

	void parseDatabase();
	void parseInput();

	float	processDate(const std::string date);
	float	processValue(const std::string value);

	// BitcoinExchange&	operator=(BitcoinExchange& other);

	// void	printMap();
};