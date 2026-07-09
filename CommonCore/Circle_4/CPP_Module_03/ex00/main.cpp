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

#include "ClapTrap.hpp"
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
    std::cout << "\n🔧 Creating robot1 using default constructor...\n";
    ClapTrap robot1;
    printStatus(robot1, "robot1");

    std::cout << "🔧 Creating robot2 named 'Optimus'...\n";
    ClapTrap robot2("Optimus");
    printStatus(robot2, "robot2");

    std::cout << "⚔️  robot2 attacks 'Megatron':\n";
    robot2.attack("Megatron");
    printStatus(robot2, "robot2 after attack");

    std::cout << "💥 robot2 takes 4 damage:\n";
    robot2.takeDamage(4);
    printStatus(robot2, "robot2 after taking damage");

    std::cout << "🔧 robot2 repairs 5 health:\n";
    robot2.beRepaired(5);
    printStatus(robot2, "robot2 after repair");

    std::cout << "📋 Copying robot2 to robot3 using copy constructor...\n";
    ClapTrap robot3 = robot2;
    printStatus(robot3, "robot3");

    std::cout << "➡️  Assigning robot3 to robot1 using assignment operator...\n";
    robot1 = robot3;
    printStatus(robot1, "robot1 after assignment");

    std::cout << "⚡ Draining robot2's energy by attacking repeatedly:\n";
    for (int i = 0; i < 10; ++i)
        robot2.attack("Starscream");
    printStatus(robot2, "robot2 after draining energy");

    std::cout << "⚠️  Attempting to attack with no energy:\n";
    robot2.attack("Starscream");

    std::cout << "⚠️  Attempting to repair with no energy:\n";
    robot2.beRepaired(3);

    std::cout << "\n✅ All tests completed.\n";
    return 0;
}

