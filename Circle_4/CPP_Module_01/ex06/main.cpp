/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:30:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/26 14:32:23 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	Harl	harl;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <Warning level>" << std::endl;
		return (0);
	}
	/*
	std::cout << "----- DEBUG -----" << std::endl;
	harl.complain("DEBUG");
	std::cout << "----- INFO -----" << std::endl;
	harl.complain("INFO");
	std::cout << "----- WARNING -----" << std::endl;
	harl.complain("WARNING");
	std::cout << "----- ERROR -----" << std::endl;
	harl.complain("ERROR");
	std::cout << "----- " << argv[1] << "-----" << std::endl;
	*/
	harl.complain(argv[1]);
	return (0);
}
