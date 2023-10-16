#include "ArrayFromFile.h"

#include<fstream>
#include<sstream>

int* ArrayFromFile(const char* fileName, uint32_t* arraySize)
{
	std::ifstream inputFile(fileName);

	if(!inputFile)
		throw std::invalid_argument("Error opeing file: " + std::string(fileName));

	uint32_t lineCount = 0;
	std::string fileContents;
	std::string line;

	while (std::getline(inputFile, line))
	{
		fileContents += line + "\n";
		lineCount++;
	}

	inputFile.close();

	std::istringstream linesStream(fileContents);

	int* array = new int[lineCount];

	for (uint32_t i = 0; i < lineCount; i++)
	{
		linesStream >> array[i];
	}

	if (arraySize)
		*arraySize = lineCount;

	return array;
}