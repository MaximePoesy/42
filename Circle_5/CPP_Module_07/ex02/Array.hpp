#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T>
class Array
{
	private:
		T* array;
		unsigned int num_elements;
	public:
		Array();
		Array(unsigned int);
		~Array();
		Array(const Array& other);
		Array& operator=(const Array& other);
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;
		unsigned int size() const;
};

#include "Array.tpp"

#endif
