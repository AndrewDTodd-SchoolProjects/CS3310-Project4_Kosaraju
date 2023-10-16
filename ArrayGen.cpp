#include "ArrayGen.h"

#include<cstdlib>
#include<ctime>

void GenerateRandomArray(int* array, const uint32_t& arrayLength, const uint32_t& minValue, const uint32_t& maxValue)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (uint32_t i = 0; i < arrayLength; i++)
	{
		array[i] = std::rand() % (maxValue - minValue + 1) + minValue;
	}
}