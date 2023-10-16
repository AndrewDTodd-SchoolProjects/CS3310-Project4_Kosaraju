#ifndef GRAPH_FROM_FILE_H
#define GRAPH_FROM_FILE_H

#include <cstdint>

#include "Graph.h"

Graph* GraphFromFile(const char* filePath, size_t* const& _graphSize = nullptr);

#endif // !GRAPH_FROM_FILE_H

