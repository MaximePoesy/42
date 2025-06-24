#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			std::cout << static_cast<char>(std::toupper((static_cast<unsigned char>(argv[i][j]))));
		}
		i++;
	}
	std::cout << std::endl;
	return (0);
}
