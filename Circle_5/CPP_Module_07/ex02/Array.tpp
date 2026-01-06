#ifndef ARRAY_TPP
# define ARRAY_TPP

#include "Array.hpp"
#include <iostream>
#include <exception>

template <typename T>
Array<T>::Array() : array(NULL), num_elements(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n)
{
    num_elements = n;
    if (n > 0)
        array = new T[n]();
    else
        array = NULL;
}

template <typename T>
Array<T>::~Array()
{
    delete[] array;
}

template <typename T>
Array<T>::Array(const Array& other) : array(NULL), num_elements(other.num_elements)
{
	if (num_elements > 0)
	{
		array = new T[num_elements];
		for (unsigned int i = 0; i < num_elements; i++)
			array[i] = other.array[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		delete[] array;
		array = NULL;
		num_elements = other.num_elements;
		
		if (num_elements > 0)
		{
			array = new T[num_elements];
			for (unsigned int i = 0; i < num_elements; i++)
				array[i] = other.array[i];
		}
	}
	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
    if (index >= num_elements)
        throw std::exception();
    return array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
    if (index >= num_elements)
        throw std::exception();
    return array[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
    return num_elements;
}

#endif
