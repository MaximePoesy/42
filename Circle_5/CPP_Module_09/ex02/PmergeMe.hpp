#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>

class PmergeMe
{
private:
    std::vector<int> _vectorData;
    std::deque<int>  _dequeData;
    size_t _comparisons;
    double _timevec;
    double _timedeque;

public:
    PmergeMe();
    ~PmergeMe();

    void parseInput(char** av);

    /* Sorting entry points */
    void sortVector();
    void sortDeque();

private:
    /* ================= VECTOR VERSION ================= */

    void fordJohnsonVector(std::vector<int>& arr);

    //recursive part of the algorythm where you divide into bigger and bigger pair of int, pair of ints, ...
    void pairVector(std::vector<int>& arr, std::vector<int>& small, std::vector<int>& large, int& leftover);

    //merge the elements back into the correct order with binary search
    void insertSmallVector(std::vector<int>& large, std::vector<int>& small);

    //binary search for the last element
    int  binarySearchVector(const std::vector<int>& arr, int value);

    std::vector<size_t> generateJacobsthal(size_t n);

    void printVector(const std::vector<int>& vec) const;

    /* ================= DEQUE VERSION ================= */

    void fordJohnsonDeque(std::deque<int>& arr);

    void pairDeque(std::deque<int>& arr, std::deque<int>& small, std::deque<int>& large, int& leftover);

    void insertSmallDeque(std::deque<int>& mainChain,
        const std::deque<int>& small);

    int  binarySearchDeque(const std::deque<int>& arr, int value);
};

#endif
