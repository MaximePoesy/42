#include "Base.hpp"
#include "Children.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

Base* generate(void)
{
	// Seed random only once (you might want to do this in main instead)
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(std::time(NULL));
		seeded = true;
	}
	
	int random = std::rand() % 3;
	
	if (random == 0)
	{
		std::cout << "Generated: A" << std::endl;
		return new A();
	}
	else if (random == 1)
	{
		std::cout << "Generated: B" << std::endl;
		return new B();
	}
	else
	{
		std::cout << "Generated: C" << std::endl;
		return new C();
	}
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Identified (pointer): A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Identified (pointer): B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Identified (pointer): C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Identified (reference): A" << std::endl;
		return;
	}
	catch (std::exception&) {}
	
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Identified (reference): B" << std::endl;
		return;
	}
	catch (std::exception&) {}
	
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "Identified (reference): C" << std::endl;
		return;
	}
	catch (std::exception&) {}
	
	std::cout << "Unknown type" << std::endl;
}
