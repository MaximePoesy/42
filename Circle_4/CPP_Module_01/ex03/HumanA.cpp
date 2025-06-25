/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:08:51 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/25 17:50:18 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <string>
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weaponType): weaponType(weaponType)
{
	this->name = name;
}

void	HumanA::attack()
{
	std::cout << name << " attacks with their " << weaponType.getType() << std::endl;
}
