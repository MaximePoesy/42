#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    std::cout << "=== Test 1: Creating valid forms ===" << std::endl;
    try {
        Form f1("Tax Form", 50, 25);
        std::cout << f1 << std::endl;
        
        Form f2("Presidential Pardon", 1, 1);
        std::cout << f2 << std::endl;
        
        Form f3("Parking Ticket", 150, 150);
        std::cout << f3 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 2: Form with grade too high ===" << std::endl;
    try {
        Form f4("Invalid Form", 0, 50);
        std::cout << f4 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 3: Form with grade too low ===" << std::endl;
    try {
        Form f5("Invalid Form", 50, 151);
        std::cout << f5 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 4: Bureaucrat signs form successfully ===" << std::endl;
    try {
        Bureaucrat bob("Bob", 30);
        Form form1("Report", 50, 25);
        
        std::cout << bob << std::endl;
        std::cout << form1 << std::endl;
        
        bob.signForm(form1);
        std::cout << form1 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 5: Bureaucrat grade too low to sign ===" << std::endl;
    try {
        Bureaucrat intern("Intern", 100);
        Form form2("Top Secret Document", 10, 5);
        
        std::cout << intern << std::endl;
        std::cout << form2 << std::endl;
        
        intern.signForm(form2);
        std::cout << form2 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 6: Signing same form twice ===" << std::endl;
    try {
        Bureaucrat alice("Alice", 1);
        Form form3("Contract", 5, 10);
        
        std::cout << alice << std::endl;
        std::cout << form3 << std::endl;
        
        alice.signForm(form3);
        std::cout << form3 << std::endl;
        
        alice.signForm(form3);
        std::cout << form3 << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 7: Multiple bureaucrats, various forms ===" << std::endl;
    try {
        Bureaucrat boss("Boss", 1);
        Bureaucrat manager("Manager", 50);
        Bureaucrat employee("Employee", 100);
        
        Form criticalForm("Critical Form", 10, 5);
        Form normalForm("Normal Form", 75, 50);
        Form trivialForm("Trivial Form", 120, 100);
        
        boss.signForm(criticalForm);
        boss.signForm(normalForm);
        boss.signForm(trivialForm);
        
        std::cout << std::endl;
        
        manager.signForm(criticalForm);
        manager.signForm(normalForm); 
        employee.signForm(trivialForm);

	std::cout << criticalForm << std::endl;
	std::cout << normalForm << std::endl;
	std::cout << trivialForm << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
