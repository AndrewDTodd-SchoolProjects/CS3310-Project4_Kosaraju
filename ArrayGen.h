#ifndef ARRAY_GEN_H
#define ARRAY_GEN_H

#include<cstdint>

/// <summary>
/// Fills a provided array with random integers
/// </summary>
/// <param name="array">The array to fill</param>
/// <param name="arrayLength">The length of the array to fill</param>
/// <param name="minValue">The smallest int value to populate the array with</param>
/// <param name="maxValue">The largest int value to populate the array with</param>
void GenerateRandomArray(int* array, const uint32_t& arrayLength, const uint32_t& minValue, const uint32_t& maxValue);

#endif // !ARRAY_GEN_H
