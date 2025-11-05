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

#include "FragTrap.hpp"
#include <iostream>

void printStatus(const FragTrap &bot, const std::string &label)
{
    std::cout << "=== " << label << " ===" << std::endl;
    std::cout << "Name   : " << bot.getName() << std::endl;
    std::cout << "Health : " << bot.getHealth() << std::endl;
    std::cout << "Energy : " << bot.getEnergy() << std::endl;
    std::cout << "Attack : " << bot.getAttack() << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::cout << "\n🛠️  Creating FragTrap 'Fraggy'...\n";
    FragTrap frag("Fraggy");
    printStatus(frag, "Fraggy");

    std::cout << "⚔️  FragTrap attacks 'Robot':\n";
    frag.attack("Robot");
    printStatus(frag, "Fraggy after attack");

    std::cout << "💥 FragTrap takes 30 damage:\n";
    frag.takeDamage(30);
    printStatus(frag, "Fraggy after taking damage");

    std::cout << "🔧 FragTrap repairs itself by 20:\n";
    frag.beRepaired(20);
    printStatus(frag, "Fraggy after repair");

    std::cout << "✋ FragTrap requests a high five:\n";
    frag.highFivesGuys();

    std::cout << "\n📋 Copying FragTrap to 'FragCopy'...\n";
    FragTrap fragCopy(frag);
    printStatus(fragCopy, "FragCopy");

    std::cout << "➡️  Assigning 'FragCopy' to 'Fraggy'...\n";
    frag = fragCopy;
    printStatus(frag, "Fraggy after assignment");

    std::cout << "\n⚡ Draining FragTrap energy completely:\n";
    for (int i = 0; i < 120; ++i)
        frag.attack("Dummy");
    frag.attack("Dummy");      // try attacking with 0 energy
    frag.beRepaired(5);        // try repairing with 0 energy
    frag.highFivesGuys();      // try high five with 0 energy
    printStatus(frag, "Fraggy after draining energy");

    std::cout << "\n✅ FragTrap-only tests completed.\n";
    return 0;
}
