#include <iostream>
#include "Array.hpp"
#include <string>

int main() {
    std::cout << "=== Test 1: Default constructor ===" << std::endl;
    Array<int> a;
    std::cout << "Expected: 0" << std::endl;
    std::cout << "Actual  : " << a.size() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Test 2: Constructor with size ===" << std::endl;
    Array<int> b(5);
    for (unsigned int i = 0; i < b.size(); ++i)
        b[i] = i * 10;
    std::cout << "Expected: 0 10 20 30 40" << std::endl;
    std::cout << "Actual  : ";
    for (unsigned int i = 0; i < b.size(); ++i)
        std::cout << b[i] << " ";
    std::cout << std::endl << std::endl;

    std::cout << "=== Test 3: Copy constructor (deep copy) ===" << std::endl;
    Array<int> c(b);
    c[0] = 100;
    std::cout << "Expected: b[0] = 0, c[0] = 100 (independent)" << std::endl;
    std::cout << "Actual  : b[0] = " << b[0] << ", c[0] = " << c[0] << std::endl;
    std::cout << std::endl;

    std::cout << "=== Test 4: Assignment operator (deep copy) ===" << std::endl;
    Array<int> d;
    d = b;
    d[1] = 200;
    std::cout << "Expected: b[1] = 10, d[1] = 200 (independent)" << std::endl;
    std::cout << "Actual  : b[1] = " << b[1] << ", d[1] = " << d[1] << std::endl;
    std::cout << std::endl;

    std::cout << "=== Test 5: String array ===" << std::endl;
    Array<std::string> sArr(2);
    sArr[0] = "Hello";
    sArr[1] = "World";
    std::cout << "Expected: Hello World" << std::endl;
    std::cout << "Actual  : " << sArr[0] << " " << sArr[1] << std::endl;
    std::cout << std::endl;

    std::cout << "=== Test 6: Out-of-bounds access ===" << std::endl;
    std::cout << "Expected: Exception caught" << std::endl;
    std::cout << "Actual  : ";
    try {
        b[10] = 42;
        std::cout << "No exception (ERROR!)" << std::endl;
    } catch (std::exception& e) {
        std::cout << "Exception caught" << std::endl;
    }

    return 0;
}
