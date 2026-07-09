#include <iostream>
#include "iter.hpp"
#include <string>

// Functions for testing
void increment(int &x) { x += 1; }
void printInt(const int &x) { std::cout << x << " "; }
void appendExclamation(std::string &s) { s += "!"; }
void printString(const std::string &s) { std::cout << s << " "; }
void doubleValue(int &x) { x *= 2; }

int main() {
    // ---------- Test 1: Integer array ----------
    int arrInt[] = {1, 2, 3, 4, 5};
    size_t lenInt = sizeof(arrInt) / sizeof(arrInt[0]);

    std::cout << "Original int array: ";
    iter(arrInt, lenInt, printInt);
    std::cout << std::endl;

    iter(arrInt, lenInt, increment);
    std::cout << "After increment:    ";
    iter(arrInt, lenInt, printInt);
    std::cout << std::endl;

    iter(arrInt, lenInt, doubleValue);
    std::cout << "After doubling:     ";
    iter(arrInt, lenInt, printInt);
    std::cout << std::endl << std::endl;

    // ---------- Test 2: Empty array ----------
    int emptyArr[0];
    std::cout << "Empty array test (should print nothing): ";
    iter(emptyArr, 0, printInt);
    std::cout << std::endl << std::endl;

    // ---------- Test 3: String array ----------
    std::string arrStr[] = {"hello", "world"};
    size_t lenStr = sizeof(arrStr) / sizeof(arrStr[0]);

    std::cout << "Original string array: ";
    iter(arrStr, lenStr, printString);
    std::cout << std::endl;

    iter(arrStr, lenStr, appendExclamation);
    std::cout << "After append '!':     ";
    iter(arrStr, lenStr, printString);
    std::cout << std::endl << std::endl;

    return 0;
}

