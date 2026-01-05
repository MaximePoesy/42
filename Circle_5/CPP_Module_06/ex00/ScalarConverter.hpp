#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <string>

class ScalarConverter
{
	private:
		ScalarConverter();
	public:
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
                ScalarConverter& operator=(const ScalarConverter& other);
		static void convert(std::string str);
};

#endif
