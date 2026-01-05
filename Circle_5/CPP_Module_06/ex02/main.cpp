#include "Base.hpp"
#include "functions.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Test 1: Single random generation ===" << std::endl;
	Base* obj1 = generate();
	identify(obj1);
	identify(*obj1);
	delete obj1;
	
	std::cout << "\n=== Test 2: Multiple generations ===" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\nIteration " << i + 1 << ":" << std::endl;
		Base* obj = generate();
		identify(obj);
		identify(*obj);
		delete obj;
	}
	
	std::cout << "\n=== Test 3: Array of objects ===" << std::endl;
	Base* objects[3];
	
	for (int i = 0; i < 3; i++)
	{
		objects[i] = generate();
	}
	
	std::cout << "\nIdentifying with pointers:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Object " << i + 1 << ": ";
		identify(objects[i]);
	}
	
	std::cout << "\nIdentifying with references:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Object " << i + 1 << ": ";
		identify(*objects[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		delete objects[i];
	}
	
	return 0;
}
