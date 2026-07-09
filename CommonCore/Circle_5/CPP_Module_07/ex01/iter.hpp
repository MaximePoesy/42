#ifndef ITER_HPP
# define ITER_HPP

template <typename T, typename U, typename V>
void iter(T* array, const U& length, V func)
{
	for (U i = 0; i < length; i++)
	{
		func(array[i]);
	}
}

#endif

