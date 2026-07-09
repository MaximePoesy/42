#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}
RPN::RPN(const RPN &other) : _stack(other._stack)
{
}
RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}
RPN::~RPN()
{
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void RPN::applyOperator(char op)
{
	long	num2;
	long	num1;
	long	result;

	if (_stack.size() < 2)
		throw std::exception();
	num2 = _stack.top();
	_stack.pop();
	num1 = _stack.top();
	_stack.pop();
	switch (op)
	{
	case '+':
		result = num1 + num2;
		break ;
	case '-':
		result = num1 - num2;
		break ;
	case '*':
		result = num1 * num2;
		break ;
	case '/':
		if (num2 == 0)
			throw std::exception();
		result = num1 / num2;
		break ;
	default:
		throw std::exception();
	}
	_stack.push(result);
}

void RPN::evaluate(const std::string &expression)
{
	if (expression.empty())
		return ;
	try
	{
		for (size_t i = 0; i < expression.size(); i++)
		{
			if (expression[i] == ' ')
				continue ;
			if (expression[i] >= '0' && expression[i] <= '9')
				_stack.push(expression[i] - '0');
			else if (isOperator(expression[i]))
				applyOperator(expression[i]);
			else
			{
				std::cerr << "Error" << std::endl;
				return ;
			}
		}
		if (_stack.size() != 1)
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		std::cout << _stack.top() << std::endl;
	}
	catch (std::exception &)
	{
		std::cerr << "Error" << std::endl;
	}
}
