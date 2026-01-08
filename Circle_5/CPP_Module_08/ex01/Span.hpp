#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <iostream>
#include <iterator>

class Span
{
private:
    unsigned int        capacity;
    std::vector<int>    numbers;

public:
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int number);

    template <typename It>
    void addNumber(It begin, It end);

    int shortestSpan() const;
    int longestSpan() const;
};

# include "Span.tpp"

#endif
