#include "Span.hpp"
#include <algorithm>
#include <exception>
#include <limits>
#include <iostream>
#include <iterator>

Span::Span(unsigned int N) : capacity(N)
{
    numbers.reserve(N);
}

Span::Span(const Span& other)
    : capacity(other.capacity), numbers(other.numbers)
{
}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        capacity = other.capacity;
        numbers = other.numbers;
    }
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
    if (numbers.size() >= capacity)
        throw std::exception();

    numbers.push_back(number);
}

int Span::shortestSpan() const
{
    if (numbers.size() < 2)
        throw std::exception();

    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = std::numeric_limits<int>::max();

    for (size_t i = 1; i < sorted.size(); ++i)
    {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < minSpan)
            minSpan = diff;
    }

    return minSpan;
}

int Span::longestSpan() const
{
    if (numbers.size() < 2)
        throw std::exception();

    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());

    return max - min;
}

