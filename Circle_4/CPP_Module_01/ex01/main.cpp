/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:46 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/25 11:39:01 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main()
{
	int	numZombie = 5;
	Zombie* horde = zombieHorde(numZombie, "fiveZombies");

	for(int	i = 0; i < numZombie; i++)
	{
		std::cout << "i : " << i << " -> ";
		horde[i].announce();
		std::cout << std::endl;
	}
	delete[] horde;
	return 0;
}
