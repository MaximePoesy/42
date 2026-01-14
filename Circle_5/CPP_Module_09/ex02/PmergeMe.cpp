#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <limits.h>

PmergeMe::PmergeMe() : _comparisons(0) {}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(char** av)
{
    _vectorData.clear();
    _dequeData.clear();

    for (int i = 0; av[i]; ++i)
    {
        char* endptr;
        long value = std::strtol(av[i], &endptr, 10);

        if (*endptr != '\0') //found bad char
        {
            std::cerr << "Error: invalid character '" << av[i] << "'" << std::endl;
            throw std::runtime_error("Invalid input");
        }

        if (value < INT_MIN || value > INT_MAX)
        {
            std::cerr << "Error: out of range: '" << av[i] << "'" << std::endl;
            throw std::runtime_error("Invalid input");
        }
	if (value < 0)
        {
            std::cerr << "Error: negative number: '" << av[i] << "'" << std::endl;
            throw std::runtime_error("Invalid input");
        }
        int intValue = static_cast<int>(value);

        // Check for duplicates
        bool duplicate = false;
        for (size_t j = 0; j < _vectorData.size(); ++j)
        {
            if (_vectorData[j] == intValue)
            {
                duplicate = true;
                break;
            }
        }
        if (duplicate)
        {
            std::cerr << "Error: duplicate number '" << intValue << "'" << std::endl;
            throw std::runtime_error("Invalid input");
        }

        _vectorData.push_back(intValue);
        _dequeData.push_back(intValue);
    }

    std::cout << "Before sorting: ";
    printVector(_vectorData);

    // Sort both
    sortVector();
    sortDeque();

    std::cout << "After sorting: ";
    printVector(_vectorData);
    std::cout << "Vector time: " << _timevec << " us" << std::endl;
    std::cout << "Deque time: " << _timedeque << " us" << std::endl;
}


void PmergeMe::sortVector()
{
    _comparisons = 0;

    clock_t start = clock();
    fordJohnsonVector(_vectorData);
    clock_t end = clock();

    _timevec = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    //std::cout << "Vector comparisons: " << _comparisons << std::endl;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
    if (arr.size() <= 1) return;

    std::vector<int> small;
    std::vector<int> large;
    int leftover = -1;

    pairVector(arr, small, large, leftover);
    fordJohnsonVector(large);
    insertSmallVector(large, small);

    if (leftover != -1)
    {
        int pos = binarySearchVector(large, leftover); //binary search might not be the best but it's fast enough
        large.insert(large.begin() + pos, leftover);
    }

    arr = large;
}

void PmergeMe::pairVector(std::vector<int>& arr, std::vector<int>& small, std::vector<int>& large, int& leftover)
{
    leftover = -1;
    size_t n = arr.size();

    if (n % 2 != 0)
    {
        leftover = arr.back();
        arr.pop_back();
        n--;
    }

    for (size_t i = 0; i < n; i += 2)
    {
        int first = arr[i];
        int second = arr[i + 1];
        ++_comparisons;

        if (first < second)
        {
            small.push_back(first);
            large.push_back(second);
        }
        else
        {
            small.push_back(second);
            large.push_back(first);
        }
    }
}

static size_t jacobsthal(size_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    size_t a = 0, b = 1, c;
    for (size_t i = 2; i <= n; ++i)
    {
        c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

static std::vector<size_t> buildJacobsthalOrder(size_t n)
{
    std::vector<size_t> order;
    std::vector<bool> used(n, false);

    size_t k = 1;
    while (1)
    {
        size_t j = jacobsthal(k);
        if (j >= n) j = n - 1;

        if (!used[j])
        {
            order.push_back(j);
            used[j] = true;
        }
        if (order.size() == n) break;

        size_t prev = jacobsthal(k - 1);
        if (prev >= n) prev = n - 1;

        for (size_t i = j; i > prev; --i)
        {
            if (!used[i - 1])
            {
                order.push_back(i - 1);
                used[i - 1] = true;
            }
        }
        if (order.size() == n) break;
        ++k;
    }

    return order;
}

void PmergeMe::insertSmallVector(std::vector<int>& large, std::vector<int>& small)
{
    std::vector<size_t> order = buildJacobsthalOrder(small.size());

    for (size_t i = 0; i < order.size(); ++i)
    {
        int value = small[order[i]];
        int pos = binarySearchVector(large, value);
        large.insert(large.begin() + pos, value);
    }
}

int PmergeMe::binarySearchVector(const std::vector<int>& arr, int value)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        ++_comparisons;
        if (arr[mid] < value) left = mid + 1;
        else right = mid;
    }
    return left;
}

void PmergeMe::printVector(const std::vector<int>& vec) const
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i != vec.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}
    
void PmergeMe::sortDeque()
{
    _comparisons = 0;

    clock_t start = clock();
    fordJohnsonDeque(_dequeData);
    clock_t end = clock();

     _timedeque = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    //std::cout << "Deque comparisons: " << _comparisons << std::endl;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1) return;

    std::deque<int> small;
    std::deque<int> large;
    int leftover = -1;

    pairDeque(arr, small, large, leftover);
    fordJohnsonDeque(large);
    insertSmallDeque(large, small);

    if (leftover != -1)
    {
        int pos = binarySearchDeque(large, leftover);
        large.insert(large.begin() + pos, leftover);
    }

    arr = large;
}

void PmergeMe::pairDeque(std::deque<int>& arr, std::deque<int>& small, std::deque<int>& large, int& leftover)
{
    leftover = -1;
    size_t n = arr.size();

    if (n % 2 != 0)
    {
        leftover = arr.back();
        arr.pop_back();
        n--;
    }

    for (size_t i = 0; i < n; i += 2)
    {
        int first = arr[i];
        int second = arr[i + 1];
        ++_comparisons;

        if (first < second)
        {
            small.push_back(first);
            large.push_back(second);
        }
        else
        {
            small.push_back(second);
            large.push_back(first);
        }
    }
}

void PmergeMe::insertSmallDeque(std::deque<int>& large, const std::deque<int>& small)
{
    std::vector<size_t> order = buildJacobsthalOrder(small.size());

    for (size_t i = 0; i < order.size(); ++i)
    {
        int value = small[order[i]];
        int pos = binarySearchDeque(large, value);
        large.insert(large.begin() + pos, value);
    }
}

int PmergeMe::binarySearchDeque(const std::deque<int>& arr, int value)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        ++_comparisons;
        if (arr[mid] < value) left = mid + 1;
        else right = mid;
    }
    return left;
}
