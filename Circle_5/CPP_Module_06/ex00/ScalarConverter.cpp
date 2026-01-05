#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <climits>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

static bool isChar(const std::string& str)
{
	return (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]));
}

static bool isInt(const std::string& str)
{
	if (str.empty())
		return false;
	
	size_t i = 0;
	
	// sign is optional
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	// must have at least one digit
	if (i >= str.length())
		return false;
	
	// must be digits
	while (i < str.length())
	{
		if (!std::isdigit(str[i]))
			return false;
		i++;
	}
	
	return true;
}

static bool isFloat(const std::string& str)
{
	// Check for special floats
	if (str == "nanf" || str == "+inff" || str == "-inff" || str == "inff")
		return true;
	
	// Must end with 'f'
	if (str.empty() || str[str.length() - 1] != 'f')
		return false;
	
	std::string numPart = str.substr(0, str.length() - 1);
	
	if (numPart.empty())
		return false;
	
	size_t i = 0;
	bool hasDot = false;
	
	// sign is optional
	if (numPart[i] == '+' || numPart[i] == '-')
		i++;
	
	if (i >= numPart.length())
		return false;
	
	// Check for digits and one point
	while (i < numPart.length())
	{
		if (numPart[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (!std::isdigit(numPart[i]))
			return false;
		i++;
	}
	
	return hasDot; // Floats must have a '.'
}

static bool isDouble(const std::string& str)
{
	// Check for special double literals
	if (str == "nan" || str == "+inf" || str == "-inf" || str == "inf")
		return true;
	
	if (str.empty())
		return false;
	
	size_t i = 0;
	bool hasDot = false;
	bool hasDigitBeforeDot = false;
	bool hasDigitAfterDot = false;
	
	// Check for sign
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	if (i >= str.length())
		return false;
	
	// Check for digits and one decimal point
	while (i < str.length())
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
			hasDigitBeforeDot = (i > 0 && std::isdigit(str[i-1])) || 
			                    (i > 1 && std::isdigit(str[i-1]) && (str[0] == '+' || str[0] == '-'));
		}
		else if (!std::isdigit(str[i]))
			return false;
		else if (hasDot)
			hasDigitAfterDot = true;
		i++;
	}
	
	// Must have decimal point, and digits on both sides
	return hasDot && hasDigitBeforeDot && hasDigitAfterDot;
}

static void printChar(double value, bool impossible)
{
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "char: impossible" << std::endl;
	else if (value < 0 || value > 127)
		std::cout << "char: impossible" << std::endl;
	else if (value < 32 || value == 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
}

static void printInt(double value, bool impossible)
{
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "int: impossible" << std::endl;
	else if (value < INT_MIN || value > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void printFloat(float value)
{
	std::cout << "float: ";
	
	if (std::isnan(value))
		std::cout << "nanf";
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inff";
		else
			std::cout << "-inff";
	}
	else
	{
		std::cout << value;
		// Only add .0 if it's a whole number AND not in scientific notation
		if (value == static_cast<int>(value) && 
		    value >= -2147483648.0f && value <= 2147483647.0f &&
		    (value > -1000000.0f && value < 1000000.0f))
			std::cout << ".0";
		std::cout << "f";
	}
	std::cout << std::endl;
}

static void printDouble(double value)
{
	std::cout << "double: ";
	
	if (std::isnan(value))
		std::cout << "nan";
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inf";
		else
			std::cout << "-inf";
	}
	else
	{
		std::cout << value;
		// Only add .0 if it's a whole number AND not in scientific notation
		if (value == static_cast<int>(value) && 
		    value >= -2147483648.0 && value <= 2147483647.0 &&
		    (value > -1000000.0 && value < 1000000.0))
			std::cout << ".0";
	}
	std::cout << std::endl;
}

static void convertFromChar(char c)
{
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void convertFromInt(int n)
{
	printChar(n, false);
	std::cout << "int: " << n << std::endl;
	printFloat(static_cast<float>(n));
	printDouble(static_cast<double>(n));
}

static void convertFromFloat(float f)
{
	printChar(f, false);
	printInt(f, false);
	printFloat(f);
	printDouble(static_cast<double>(f));
}

static void convertFromDouble(double d)
{
	printChar(d, false);
	printInt(d, false);
	printFloat(static_cast<float>(d));
	printDouble(d);
}

static bool stringToInt(const std::string& str, int& result)
{
	// to get the full number in all cases
	std::stringstream ss(str);
	long long temp;
	ss >> temp;
	
	if (ss.fail() || !ss.eof())
		return false;
	
	if (temp < INT_MIN || temp > INT_MAX)
		return false;
	
	result = static_cast<int>(temp);
	return true;
}

static float stringToFloat(const std::string& str)
{
	if (str == "nanf")
		return std::numeric_limits<float>::quiet_NaN();
	if (str == "+inff" || str == "inff")
		return std::numeric_limits<float>::infinity();
	if (str == "-inff")
		return -std::numeric_limits<float>::infinity();
	
	// Remove 'f' at the end
	std::string numStr = str.substr(0, str.length() - 1);
	return static_cast<float>(std::atof(numStr.c_str()));
}

static double stringToDouble(const std::string& str)
{
	if (str == "nan")
		return std::numeric_limits<double>::quiet_NaN();
	if (str == "+inf" || str == "inf")
		return std::numeric_limits<double>::infinity();
	if (str == "-inf")
		return -std::numeric_limits<double>::infinity();
	
	return std::atof(str.c_str());
}

void ScalarConverter::convert(std::string str)
{
	if (isChar(str))
	{
		char c = str[0];
		convertFromChar(c);
	}
	else if (isInt(str))
	{
		int value;
		if (stringToInt(str, value))
			convertFromInt(value);
		else 
		{
			// Integer overflow
			double d = stringToDouble(str);
			convertFromDouble(d);
		}
	}
	else if (isFloat(str))
	{
		float value = stringToFloat(str);
		convertFromFloat(value);
	}
	else if (isDouble(str))
	{
		double value = stringToDouble(str);
		convertFromDouble(value);
	}
	else
	{
		std::cout << "Error: Invalid literal" << std::endl;
	}
}
