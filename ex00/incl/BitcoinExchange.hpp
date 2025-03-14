#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include <iomanip>


class BitcoinExchange
{
private:
	std::string							_inputFile;
	std::string							_dataFile = "data.csv";
	std::map<int, float>				_dataMap;
	std::string							_errorMsg;

public:
	BitcoinExchange(std::string inputFile);
	BitcoinExchange(BitcoinExchange& other);
	~BitcoinExchange();

	void parseDatabase();
	void parseInput();

	float	processDate(int inputDate);

	BitcoinExchange&	operator=(BitcoinExchange& other);

	bool	inputIsValid(const std::string buffer);
	bool	dateIsValid(const std::string dateStr);
	int		dateToInt(const std::string dateStr);
	// void	printMap();
};
