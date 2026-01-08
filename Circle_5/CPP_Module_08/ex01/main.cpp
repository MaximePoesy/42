#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
    try
    {
        std::cout << "=== 42 test ===" << std::endl;
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;

        std::cout << "\n=== Iterator range test ===" << std::endl;
        Span big(10001);
        std::vector<int> values;

        for (int i = 0; i < 10000; ++i)
            values.push_back(i);
	values.push_back(10002);
	
        big.addNumber(values.begin(), values.end());

        std::cout << "Big shortest span: " << big.shortestSpan() << std::endl;
        std::cout << "Big longest span : " << big.longestSpan() << std::endl;

        std::cout << "\n=== Exception test ===" << std::endl;
        try
        {
            Span small(1);
            small.addNumber(42);
            small.shortestSpan(); // should throw
        }
        catch (const std::exception&)
        {
            std::cout << "Exception thrown (not enough elements) (expected)" << std::endl;
        }
    }
    catch (const std::exception&)
    {
        std::cout << "Unexpected exception! (not good uh oh)" << std::endl;
    }

    return 0;
}

