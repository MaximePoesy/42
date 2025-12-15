#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
	std::cout << "=== Test 1: Create all form types ===" << std::endl;
	try {
		ShrubberyCreationForm shrub("home");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Arthur Dent");
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << pardon << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Signing forms ===" << std::endl;
	try {
		Bureaucrat low("Intern", 150);
		Bureaucrat mid("Manager", 50);
		Bureaucrat high("CEO", 1);
		
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("Marvin");
		PresidentialPardonForm pardon("Ford Prefect");
		
		std::cout << "\nIntern trying to sign Shrubbery (needs 145):" << std::endl;
		low.signForm(shrub);
		
		std::cout << "\nManager trying to sign Robotomy (needs 72):" << std::endl;
		mid.signForm(robot);
		
		std::cout << "\nCEO signing Robotomy:" << std::endl;
		high.signForm(robot);
		
		std::cout << "\nCEO signing Presidential Pardon (needs 25):" << std::endl;
		high.signForm(pardon);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Executing unsigned form ===" << std::endl;
	try {
		Bureaucrat ceo("CEO", 1);
		ShrubberyCreationForm shrub("office");
		
		std::cout << "Trying to execute unsigned form:" << std::endl;
		ceo.executeForm(shrub);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Executing with insufficient grade ===" << std::endl;
	try {
		Bureaucrat low("Intern", 150);
		Bureaucrat high("CEO", 1);
		ShrubberyCreationForm shrub("park");
		
		high.signForm(shrub);
		
		std::cout << "Intern trying to execute (needs 137, has 150):" << std::endl;
		low.executeForm(shrub);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Successful execution - Shrubbery ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("backyard");
		
		boss.signForm(shrub);
		boss.executeForm(shrub);
		std::cout << "Check backyard_shrubbery file!" << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Successful execution - Robotomy ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm robot("Target Alpha");
		
		boss.signForm(robot);
		boss.executeForm(robot);
		
		std::cout << "\nTrying robotomy again (50% success rate):" << std::endl;
		RobotomyRequestForm robot2("Target Beta");
		boss.signForm(robot2);
		boss.executeForm(robot2);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 7: Successful execution - Presidential Pardon ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Zaphod himself");
		
		boss.signForm(pardon);
		boss.executeForm(pardon);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 8: Complex scenario ===" << std::endl;
	try {
		Bureaucrat president("President", 1);
		Bureaucrat vicePresident("Vice President", 5);
		Bureaucrat director("Director", 40);
		Bureaucrat manager("Manager", 70);
		Bureaucrat intern("Intern", 145);
		
		ShrubberyCreationForm shrub("headquarters");
		RobotomyRequestForm robot("Obsolete Employee");
		PresidentialPardonForm pardon("Convicted Criminal");
		
		std::cout << "\nIntern signs and executes Shrubbery:" << std::endl;
		intern.signForm(shrub);
		intern.executeForm(shrub);
		
		std::cout << "\nManager tries Robotomy (can sign at 72, can't execute at 45):" << std::endl;
		manager.signForm(robot);
		manager.executeForm(robot);
		
		std::cout << "\nDirector executes Robotomy:" << std::endl;
		director.executeForm(robot);
		
		std::cout << "\nVice President tries Presidential Pardon (can't sign at 25, can execute at 5):" << std::endl;
		vicePresident.signForm(pardon);
		
		std::cout << "\nPresident signs and executes Presidential Pardon:" << std::endl;
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (const std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
