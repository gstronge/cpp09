#include "../incl/BitcoinExchange.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "error: usage ./btc filename.txt\n";
		return 1;
	}
	BitcoinExchange		btx(argv[1]);
	btx.parseDatabase();
	btx.parseInput();


	// btx.printMap();
	return 0;
}