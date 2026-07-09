#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
	Data originalData;
	originalData.id = 42;
	originalData.name = "Test Data";
	originalData.value = 3.14159;
	
	Data* originalPtr = &originalData;
	// A
	std::cout << "Original pointer: " << originalPtr << std::endl;
	std::cout << "Data values: id=" << originalData.id 
	          << ", name=" << originalData.name 
	          << ", value=" << originalData.value << std::endl;
	std::cout << std::endl;
	// A -> B
	uintptr_t serialized = Serializer::serialize(originalPtr);
	std::cout << "Serialized: " << serialized << std::endl;
	std::cout << std::endl;
	// B -> A
	Data* deserializedPtr = Serializer::deserialize(serialized);
	// A
	std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
	std::cout << "Data values: id=" << deserializedPtr->id 
	          << ", name=" << deserializedPtr->name 
	          << ", value=" << deserializedPtr->value << std::endl;
	std::cout << std::endl;
	
	if (originalPtr == deserializedPtr)
		std::cout << "Success: pointers are equal" << std::endl;
	else
		std::cout << "Error: pointers are not equal" << std::endl;
	
	return 0;
}
