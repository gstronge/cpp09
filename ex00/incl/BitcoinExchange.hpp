#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include <iomanip>


class BitcoinExchange
{
private:
	const std::string							_inputFile;
	const std::string							_dataFile = "data.csv";
	// std::map<std::string, float>				_dataMap;
	std::map<int, float>						_dataMap;
	std::string									_errorMsg;

public:
	BitcoinExchange(const std::string inputFile);
	// BitcoinExchange(BitcoinExchange& other);
	~BitcoinExchange();

	void parseDatabase();
	void parseInput();

	float	processDate(int inputDate);

	// BitcoinExchange&	operator=(BitcoinExchange& other);

	bool	inputIsValid(const std::string buffer);
	bool	dateIsValid(const std::string dateStr);
	int		dateToInt(const std::string dateStr);
	// void	printMap();
};
