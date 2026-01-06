#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
    // Test with vector
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    try {
        std::vector<int>::iterator it = easyfind(vec, 3);
        std::cout << "Found in vector: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "Not found in vector" << std::endl;
    }
    
    try {
        easyfind(vec, 42);
        std::cout << "Found 42 in vector" << std::endl;
    } catch (std::exception& e) {
        std::cout << "42 not found in vector" << std::endl;
    }
    
    // Test with list
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    
    try {
        std::list<int>::iterator it = easyfind(lst, 20);
        std::cout << "Found in list: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "Not found in list" << std::endl;
    }
    
    try {
        easyfind(lst, 100);
        std::cout << "Found 100 in list" << std::endl;
    } catch (std::exception& e) {
        std::cout << "100 not found in list" << std::endl;
    }
    
    return 0;
}
