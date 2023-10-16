#ifndef RANDOM_RANGE_H
#define RANDOM_RANGE_H

#include<cstdlib>
#include<ctime>

template <typename T>
T RandomRange(const T& min, const T& max)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	return static_cast<T>(std::rand() % (max - min + 1) + min);
}

#endif //!RANDOM_RANGE_H
