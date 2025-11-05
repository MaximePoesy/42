/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:36:29 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/10 13:03:27 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

static void printHeader(const std::string &s)
{
	std::cout << "\n===== " << s << " =====" << std::endl;
}

static void printStats(const DiamondTrap &d)
{
	std::cout << "Name (DiamondTrap): " << d.getName() << std::endl;
	std::cout << "Hit points:         " << d.getHealth() << std::endl;
	std::cout << "Energy points:      " << d.getEnergy() << std::endl;
	std::cout << "Attack damage:      " << d.getAttack() << std::endl;
}

int main()
{
	printHeader("1) Create DiamondTrap (constructor messages should appear)");
	DiamondTrap dt("Bumblebee");
	printStats(dt);

	printHeader("2) Call whoAmI() (shows DiamondTrap name and ClapTrap name)");
	dt.whoAmI();
	printStats(dt);

	printHeader("3) Use attack() once (ScavTrap::attack). Check energy decrement");
	dt.attack("Decepticon");
	printStats(dt);

	printHeader("4) Take damage (30) and show stats");
	dt.takeDamage(30);
	printStats(dt);

	printHeader("5) Be repaired (20) and show stats");
	dt.beRepaired(20);
	printStats(dt);

	printHeader("6) Attack until energy runs out (loop shows each step)");
	// attack many times to observe energy dropping (and behavior when 0)
	for (int i = 0; i < 6; ++i)
	{
		std::cout << "-- attack iteration " << (i + 1) << " --" << std::endl;
		dt.attack("Target");
		printStats(dt);
	}

	printHeader("7) Copy-construct a new DiamondTrap from dt and show its stats");
	DiamondTrap copy(dt);
	copy.whoAmI();
	printStats(copy);

	printHeader("8) Assign to another DiamondTrap and show its stats");
	DiamondTrap assigned("Optimus");
	std::cout << "(before assignment) assigned:" << std::endl;
	printStats(assigned);
	assigned = dt;
	std::cout << "(after assignment) assigned:" << std::endl;
	printStats(assigned);

	printHeader("9) End of tests — destructors will run when variables go out of scope");
	return 0;
}
