#ifndef AFORM_HPP
# define AFORM_HPP
# include <string>
# include <exception>
# include <iostream>

class Bureaucrat;

class AForm
{
  private:
	std::string const name;
	bool is_signed;
	int const sign_grade;
	int const exec_grade;

  public:
	AForm();
	AForm(std::string name, int sign_grade, int exec_grade);
	virtual ~AForm();
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);

	std::string const &getName() const;
	bool getSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	void beSigned(Bureaucrat &b);
	
	virtual void execute(Bureaucrat const & executor) const = 0;

	class GradeTooHighException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class FormNotSignedException : public std::exception
	{
	public:
		const char* what() const throw();
	};
};

std::ostream &operator<<(std::ostream& os, const AForm& f);

#endif
