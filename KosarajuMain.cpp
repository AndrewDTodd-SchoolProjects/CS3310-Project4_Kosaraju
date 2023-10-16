#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdint>
#include <vector>
#include <cstring>

#include "Graph.h"
#include "GraphFromFile.h"

#ifdef _LINUX_BUILD
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#elif defined(_WINDOWS_BUILD)
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _LINUX_BUILD
	const rlim_t desiredStackSize = 1024ll * 1024ll * 1024ll; // 1 GiB in bytes

	struct rlimit rl;
	if (getrlimit(RLIMIT_STACK, &rl) == 0) {
		if (rl.rlim_cur < desiredStackSize) {
			rl.rlim_cur = desiredStackSize;
			if (setrlimit(RLIMIT_STACK, &rl) != 0) {
				perror("setrlimit");
				return EXIT_FAILURE;
			}
		}
	}
	else {
		perror("getrlimit");
		return EXIT_FAILURE;
	}
#elif defined(_WINDOWS_BUILD)
	const SIZE_T desiredStackSize = 1024ll * 1024ll * 1024ll; // 1 GiB in bytes
	if (!SetThreadStackGuarantee(&desiredStackSize)) {
		printf("Failed to set the thread stack size.\n");
		return EXIT_FAILURE;
	}
#endif // _LINUX_BUILD


	Graph* _graph = nullptr;
	size_t _graphSize = 0;
	char* _filePath = nullptr;
	bool _filePathAllocated = false;
	uint8_t _numBigestSCCToGet = 5;
	bool debugInfo = false;
	
	if (argc < 2)
	{
		std::string filePath;
		std::cout << "Enter a path to a file containing the graph edge definitions: ";
		getline(std::cin, filePath);

		_filePath = new char[filePath.size() + 1];
		std::strcpy(_filePath, filePath.c_str());
		_filePathAllocated = true;
	}
	else
	{
		std::string secondArg = argv[1];
		if (secondArg == "-d")
		{
			debugInfo = true;

			_filePath = argv[2];

			if (argc == 4)
			{
				std::string arg3 = argv[4];
				try
				{
					_numBigestSCCToGet = static_cast<uint8_t>(std::stoi(arg3));
				}
				catch (std::exception ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " continuing with default of 5" << std::endl;
					_numBigestSCCToGet = 5;
				}
			}
			else if (argc > 4)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg3 = argv[4];
				try
				{
					_numBigestSCCToGet = static_cast<uint8_t>(std::stoi(arg3));
				}
				catch (std::exception ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " continuing with default of 5" << std::endl;
					_numBigestSCCToGet = 5;
				}
			}
		}
		else
		{
			_filePath = argv[1];

			if (argc == 3)
			{
				std::string arg3 = argv[3];
				try
				{
					_numBigestSCCToGet = static_cast<uint8_t>(std::stoi(arg3));
				}
				catch (std::exception ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " continuing with default of 5" << std::endl;
					_numBigestSCCToGet = 5;
				}
			}
			else if (argc > 3)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg3 = argv[3];
				try
				{
					_numBigestSCCToGet = static_cast<uint8_t>(std::stoi(arg3));
				}
				catch (std::exception ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " continuing with default of 5" << std::endl;
					_numBigestSCCToGet = 5;
				}
			}
		}
	}

	std::chrono::milliseconds total = std::chrono::milliseconds();
	std::chrono::_V2::system_clock::time_point startTime;
	std::chrono::_V2::system_clock::time_point endTime;
	std::chrono::milliseconds duration;
	try
	{
		if (debugInfo)
		{
			startTime = std::chrono::high_resolution_clock::now();
		}
		_graph = GraphFromFile(_filePath, &_graphSize);
		if (debugInfo)
		{
			endTime = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

			std::cout << "Graph with " << _graphSize << " elements loaded in" << std::endl;
			std::cout << "Loading Graph from file took ~" << duration.count() << " milliseconds" << std::endl;
		}
	}
	catch (std::invalid_argument argEx)
	{
		std::cerr << "Error: " << argEx.what() << std::endl;
		if(_filePathAllocated)
			delete[] _filePath;
		
		return 1;
	}

	std::vector<std::vector<int>*>* _sccList = new std::vector<std::vector<int>*>;


	if (debugInfo)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
	_graph->getSCCs(_sccList);
	if (debugInfo)
	{
		endTime = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::cout << "Calculating SCCs from graph took ~" << duration.count() << " milliseconds" << std::endl;
	}

	//needed to arrange the nested vectors (SCCs) in descending order of their sizes
	std::sort(_sccList->begin(), _sccList->end(), [](const std::vector<int>* a, const std::vector<int>* b) {return a->size() > b->size(); });

	if (debugInfo)
	{
		std::cout << "Printing the first " << static_cast<uint32_t>(_numBigestSCCToGet) << " SCCs with the most elements in the SCC" << std::endl;
	}

	int printedCount = 0;
	for (auto scc : *_sccList)
	{
		if (printedCount < _numBigestSCCToGet)
		{
			std::cout << scc->size() << ',';
			printedCount++;
		}
		else
			break;
	}
	while (printedCount < _numBigestSCCToGet)
	{
		std::cout << "0,";
		printedCount++;
	}
	std::cout << std::endl;

	if(_filePathAllocated)
		delete[] _filePath;

	for (int i = 0; i < _sccList->size(); i++)
	{
		delete _sccList->at(i);
	}
	delete _sccList;

	return 0;
}
