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

#include "ScavTrap.hpp"
#include <iostream>

void printStatus(const ClapTrap& bot, const std::string& label)
{
    std::cout << "=== " << label << " ===" << std::endl;
    std::cout << "Name   : " << bot.getName() << std::endl;
    std::cout << "Health : " << bot.getHealth() << std::endl;
    std::cout << "Energy : " << bot.getEnergy() << std::endl;
    std::cout << "Attack : " << bot.getAttack() << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "\n🤖 Creating basic ClapTrap...\n";
    ClapTrap basic("Clappy");
    printStatus(basic, "basic ClapTrap");

    std::cout << "\n🧱 Creating ScavTrap 'Gatekeeper'...\n";
    ScavTrap gatekeeper("Gatekeeper");
    printStatus(gatekeeper, "ScavTrap Gatekeeper");

    std::cout << "⚔️  ScavTrap attacks 'Bandit':\n";
    gatekeeper.attack("Bandit");
    printStatus(gatekeeper, "Gatekeeper after attack");

    std::cout << "💥 ScavTrap takes 42 damage:\n";
    gatekeeper.takeDamage(42);
    printStatus(gatekeeper, "Gatekeeper after taking damage");

    std::cout << "🔧 ScavTrap repairs itself by 10:\n";
    gatekeeper.beRepaired(10);
    printStatus(gatekeeper, "Gatekeeper after repair");

    std::cout << "🛡️  Activating Gatekeeper mode:\n";
    gatekeeper.guardGate();

    std::cout << "\n📋 Copying ScavTrap to 'CopyBot'...\n";
    ScavTrap copyBot(gatekeeper);
    printStatus(copyBot, "CopyBot");

    std::cout << "➡️  Assigning 'CopyBot' to 'basic' ClapTrap...\n";
    basic = copyBot;
    printStatus(basic, "basic after assignment");

    std::cout << "\n⚡ Draining ScavTrap’s energy completely:\n";
    for (int i = 0; i < 50; ++i)
        gatekeeper.attack("Dummy target");
    printStatus(gatekeeper, "Gatekeeper after draining energy");

    std::cout << "⚠️  Trying to attack with 0 energy:\n";
    gatekeeper.attack("Dummy target");

    std::cout << "⚠️  Trying to repair with 0 energy:\n";
    gatekeeper.beRepaired(5);

    std::cout << "\n✅ All ScavTrap tests completed.\n\n";

    return 0;
}
