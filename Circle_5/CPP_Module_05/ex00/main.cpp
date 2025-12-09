#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    // Basic valid usage
    try {
        Bureaucrat a("Alice", 2);
        std::cout << a << std::endl;

        a.incrGrade();   // -> grade 1
        std::cout << a << std::endl;

        a.incrGrade();   // Should throw: grade too high
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "-----" << std::endl;

    // Another valid range test
    try {
        Bureaucrat b("Bob", 149);
        std::cout << b << std::endl;

        b.decrGrade();   // -> 150
        std::cout << b << std::endl;

        b.decrGrade();   // Should throw: grade too low
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "-----" << std::endl;

    // Invalid construction
    try {
        Bureaucrat c("Charlie", 151);   // Should throw immediately
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "-----" << std::endl;

    //should be no issue
    try {
        Bureaucrat d("Charlie");   // Should throw immediately
	std::cout << d << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
