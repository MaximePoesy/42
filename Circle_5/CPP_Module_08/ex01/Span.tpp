#include <vector>
#include "Span.hpp"
#include <iostream>
#include <iterator>

template <typename It>
void Span::addNumber(It begin, It end)
{
    unsigned int distance = std::distance(begin, end);
    if (numbers.size() + distance > capacity)
        throw std::exception();
    numbers.insert(numbers.end(), begin, end);
}
