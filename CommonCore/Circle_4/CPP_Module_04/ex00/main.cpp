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
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    std::cout << "===== Correct Animal =====" << std::endl;

    const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << std::endl;
    std::cout << "Dog type: " << dog->getType() << std::endl;
    std::cout << "Cat type: " << cat->getType() << std::endl;
    std::cout << "Animal type: " << meta->getType() << std::endl;
    std::cout << std::endl;

    std::cout << "Sounds:" << std::endl;
    cat->makeSound();  // Should print Cat sound
    dog->makeSound();  // Should print Dog sound
    meta->makeSound(); // Should print Animal sound

    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "===== Wrong Animal =====" << std::endl;

    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << std::endl;
    std::cout << "WrongCat type: " << wrongCat->getType() << std::endl;
    std::cout << "WrongAnimal type: " << wrongMeta->getType() << std::endl;
    std::cout << std::endl;

    std::cout << "Sounds:" << std::endl;
    wrongCat->makeSound();   // Will print WrongAnimal sound (not Cat)
    wrongMeta->makeSound();  // Will print WrongAnimal sound

    std::cout << std::endl;

    return 0;
}
