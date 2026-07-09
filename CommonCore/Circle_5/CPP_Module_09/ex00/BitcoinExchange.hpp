#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float> database;
		
		bool isValidValue(float value);
		float findClosestRate(const std::string& date);
		void loadDatabase(const std::string& filename);
		void processLine(const std::string& line);
		
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		
		void processInputFile(const std::string& filename);
};

#endif
