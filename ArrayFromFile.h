#ifndef ARRAY_FROM_FILE_H
#define ARRAY_FROM_FILE_H

#include<cstdint>

/// <summary>
/// Reads a file that is expected to be formatted with one number per line and creates an array of ints populated with those numbers
/// </summary>
/// <param name="fileName">A C style string with the file path</param>
/// <param name="arraySize">A reference to a 32 bit unsigned int to get the length of the array if it is wanted</param>
/// <returns>A pointer to a created and populated array</returns>
int* ArrayFromFile(const char* fileName, uint32_t* arraySize = nullptr);

#endif // !ARRAY_FROM_FILE_H

