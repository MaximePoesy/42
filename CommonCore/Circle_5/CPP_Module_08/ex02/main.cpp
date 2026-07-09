#include "MutantStack.hpp"
#include <list>
#include <iostream>

int main()
{
    std::cout << "=== Testing MutantStack<int> ===" << std::endl;
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "Top element: " << mstack.top() << std::endl;
    std::cout << "Size: " << mstack.size() << std::endl;

    std::cout << "Iterating over MutantStack: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Reverse iterating over MutantStack: ";
    for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;

    std::cout << "\n=== Testing std::list<int> with same elements ===" << std::endl;
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(17);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);

    std::cout << "Top element: " << "Doesnt exist. A list doesn't have a top/front" << std::endl;
    std::cout << "Size: " << lst.size() << std::endl;

    std::cout << "Iterating over std::list: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Reverse iterating over std::list: ";
    for (std::list<int>::reverse_iterator rit = lst.rbegin(); rit != lst.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;

    return 0;
}

