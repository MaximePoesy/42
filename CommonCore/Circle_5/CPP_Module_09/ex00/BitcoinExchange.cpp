#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	database = other.database;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		database = other.database;
	return *this;
}

static bool extractDate(const std::string& s)
{
	int y, m, d;
	char dash1, dash2;

	std::istringstream iss(s);
	if (!(iss >> y >> dash1 >> m >> dash2 >> d) || dash1 != '-' || dash2 != '-')
		return false;

	struct tm t = {};
	t.tm_year = y - 1900;
	t.tm_mon = m - 1;
	t.tm_mday = d;

	time_t time = mktime(&t);
	if (time == -1)
		return false;

	return (t.tm_year == y - 1900 &&
			t.tm_mon == m - 1 &&
			t.tm_mday == d);
}


void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		std::string date = line.substr(0, comma);
		float rate = std::atof(line.substr(comma + 1).c_str());

		if (extractDate(date))
			database[date] = rate;
	}
}

bool BitcoinExchange::isValidValue(float value)
{
	return value >= 0.0f && value <= 1000.0f;
}

float BitcoinExchange::findClosestRate(const std::string& date)
{
	std::map<std::string, float>::iterator it = database.upper_bound(date);
	if (it == database.begin())
		throw std::exception();
	--it;
	return it->second;
}

void BitcoinExchange::processLine(const std::string& line)
{
	size_t sep = line.find(" | ");
	if (sep == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, sep);
	std::string valueStr = line.substr(sep + 3);

	if (!extractDate(date))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}

	char* end;
	float value = std::strtof(valueStr.c_str(), &end);
	if (*end != '\0')
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}

	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}

	if (!isValidValue(value))
	{
		std::cerr << "Error: too large a number." << std::endl;
		return;
	}

	try
	{
		float rate = findClosestRate(date);
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
	}
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		processLine(line);
	}
}


