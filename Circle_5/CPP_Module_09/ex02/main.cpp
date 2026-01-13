#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Wrong number of parameters" << std::endl;
        return 0;
    }
    ++argv;
    PmergeMe pm;
    pm.parseInput(argv);

    return 0;
}