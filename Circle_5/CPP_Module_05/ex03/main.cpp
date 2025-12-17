#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1);
	AForm* form;

	std::cout << "=== Test 1: Valid forms ===" << std::endl;
	form = someRandomIntern.makeForm("robotomy request", "me");
	if (form) {
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	std::cout << "\n=== Test 2: Another valid form ===" << std::endl;
	form = someRandomIntern.makeForm("shrubbery creation", "trees");
	if (form) {
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	std::cout << "\n=== Test 3: Invalid form ===" << std::endl;
	form = someRandomIntern.makeForm("invalid form", "target");
	if (form) {
		delete form;
	}

	return 0;
}
