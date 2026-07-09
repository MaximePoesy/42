/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:08:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/25 17:44:31 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <string>
#include <iostream>

void	HumanB::setWeapon(Weapon	&weaponType)
{
	this->weaponType = &weaponType;
}

HumanB::HumanB(std::string name)
{
	this->weaponType = NULL;
	this->name = name;
}

void	HumanB::attack()
{
	if (weaponType)
		std::cout << name << " attacks with their " << weaponType->getType() << std::endl;
	else
		std::cout << name << " has no weapon to attack with." << std::endl;
}
