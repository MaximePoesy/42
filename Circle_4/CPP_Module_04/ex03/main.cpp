/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:36:29 by mpoesy            #+#    #+#             */
/*   Updated: 2025/11/05 17:12:02 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

void separator(const std::string &title)
{
    std::cout << "\n===== " << title << " =====" << std::endl;
}

int main()
{
    separator("Basic usage test from subject");
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());

        ICharacter* me = new Character("me");
        AMateria* tmp;

        tmp = src->createMateria("ice");
        me->equip(tmp);
        tmp = src->createMateria("cure");
        me->equip(tmp);

        ICharacter* bob = new Character("bob");

        me->use(0, *bob);
        me->use(1, *bob);

        delete bob;
        delete me;
        delete src;
    }

    separator("Trying to learn more than 4 Materias");
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        src->learnMateria(new Ice()); // should be ignored safely
        delete src;
    }

    separator("Trying to equip more than 4 Materias");
    {
        ICharacter* alice = new Character("Alice");
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());

        for (int i = 0; i < 6; i++)
        {
            AMateria* tmp = src->createMateria(i % 2 ? "ice" : "cure");
            alice->equip(tmp);
        }

        delete src;
        delete alice;
    }

    separator("Using and unequipping Materias");
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());

        Character me("me");
        Character target("enemy");

        AMateria* ice = src->createMateria("ice");
        AMateria* cure = src->createMateria("cure");
        me.equip(ice);
        me.equip(cure);

        std::cout << "-- Using Materias --" << std::endl;
        me.use(0, target);
        me.use(1, target);

        std::cout << "-- Unequipping slots 0 & 1 --" << std::endl;
        me.unequip(0);
        me.unequip(1);
        me.use(0, target); // should do nothing
        me.use(1, target);

        delete src;
        // ice and cure unequipped must be handled externally
        delete ice;
        delete cure;
    }

    separator("Deep copy of Character");
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());

        Character original("Original");
        original.equip(src->createMateria("ice"));
        original.equip(src->createMateria("cure"));

        std::cout << "-- Creating copy --" << std::endl;
        Character copy = original; // invokes copy constructor

        Character target("Target");
        std::cout << "-- Using original's Materias --" << std::endl;
        original.use(0, target);
        original.use(1, target);

        std::cout << "-- Using copy's Materias --" << std::endl;
        copy.use(0, target);
        copy.use(1, target);

        std::cout << "-- Destroying everything --" << std::endl;
        delete src;
    }

    separator("MateriaSource deep copy test");
    {
        MateriaSource source;
        source.learnMateria(new Ice());
        source.learnMateria(new Cure());

        std::cout << "-- Copy constructing a new source --" << std::endl;
        MateriaSource copy(source);

        Character hero("Hero");
        AMateria* tmp;

        tmp = copy.createMateria("ice");
        hero.equip(tmp);
        tmp = copy.createMateria("cure");
        hero.equip(tmp);

        Character boss("Boss");
        hero.use(0, boss);
        hero.use(1, boss);
    }

    separator("Invalid type test");
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        AMateria* tmp = src->createMateria("fire"); // unknown type
        if (!tmp)
            std::cout << "Could not create 'fire' materia (as expected)" << std::endl;
        delete src;
    }

    separator("Out-of-bounds and null safety");
    {
        Character test("Tester");
        test.use(-1, test);
        test.use(5, test);
        test.unequip(-2);
        test.unequip(4);
        test.equip(NULL);
    }

    separator("All tests completed successfully");
    return 0;
}


