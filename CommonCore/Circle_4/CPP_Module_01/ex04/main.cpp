/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:04 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/26 10:17:30 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

bool	replaceAndWrite(const std::string &inputFile, const std::string &s1,
		const std::string &s2)
{
	std::ifstream infile(inputFile.c_str());
	if (!infile)
	{
		std::cerr << "Error: Cannot open input file: " << inputFile << std::endl;
		return (false);
	}
	std::string outputFile = inputFile + ".replace";
	std::ofstream outfile(outputFile.c_str());
	if (!outfile)
	{
		std::cerr << "Error: Cannot create output file: " << outputFile << std::endl;
		return (false);
	}
	std::string line;
	while (std::getline(infile, line))
	{
		std::string result;
		std::size_t pos = 0;
		while (true)
		{
			std::size_t found = line.find(s1, pos);
			if (found == std::string::npos) // npos = max size_t
			{
				result += line.substr(pos); // append the rest of the line
				break ;
			}
			result += line.substr(pos, found - pos); // append text before s1
			result += s2;                            // append replacement
			pos = found + s1.length();               // move past s1 (for std::string::find)
		}
		outfile << result << std::endl;
	}
	infile.close();
	outfile.close();
	return (true);
}

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	std::string filename(argv[1]);
	std::string s1(argv[2]);
	std::string s2(argv[3]);
	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be an empty string." << std::endl;
		return (1);
	}
	if (!replaceAndWrite(filename, s1, s2))
	{
		return (1);
	}
	std::cout << "File processed successfully. Output written to: " << filename << ".replace" << std::endl;
	return (0);
}
