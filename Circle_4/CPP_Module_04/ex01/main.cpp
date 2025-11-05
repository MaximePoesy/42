/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:36:29 by mpoesy            #+#    #+#             */
/*   Updated: 2025/11/05 16:11:19 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main()
{
    std::cout << "===== Basic Creation and Deletion =====" << std::endl;
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete j; // should not leak
    delete i;

    std::cout << std::endl;
    
    std::cout << "===== Array of Animals =====" << std::endl;

    const int size = 6;
    Animal* animals[size];

    // Fill first half with Dogs, second half with Cats
    for (int idx = 0; idx < size; idx++)
    {
        if (idx < size / 2)
            animals[idx] = new Dog();
        else
            animals[idx] = new Cat();
    }

    std::cout << std::endl;
    std::cout << "===== Deleting Animals =====" << std::endl;
    for (int idx = 0; idx < size; idx++)
        delete animals[idx]; // deletes as Animal*, calls proper destructors

    std::cout << std::endl;
    std::cout << "===== Deep Copy Test (Dog) =====" << std::endl;
    Dog basicDog;
    {
        Dog copyDog = basicDog; // calls copy constructor (deep copy)
        std::cout << "Exiting scope of copyDog..." << std::endl;
    } // copyDog destroyed, basicDog must still have its Brain intact
    std::cout << "Back in main, basicDog still alive!" << std::endl;

    std::cout << std::endl;
    std::cout << "===== Deep Copy Test (Cat) =====" << std::endl;
    Cat basicCat;
    {
        Cat copyCat;
        copyCat = basicCat; // calls copy assignment (deep copy)
        std::cout << "Exiting scope of copyCat..." << std::endl;
    } // copyCat destroyed, basicCat must still have its Brain intact

    std::cout << std::endl;
    std::cout << "===== End of main =====" << std::endl;
    
    return 0;
}
