#include "GraphFromFile.h"

#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <unordered_set>

#include "Graph.h"

Graph* GraphFromFile(const char* filePath, size_t* const& _graphSize)
{
	std::ifstream inputFile(filePath);
	if(!inputFile)
		throw std::invalid_argument("Error opeing file: " + std::string(filePath));

	std::vector<std::pair<int, int>> _edges;
	std::unordered_set<int> _uniqueVerts;

	int v, w;
	while (inputFile >> v >> w)
	{
		_uniqueVerts.insert(v);
		_uniqueVerts.insert(w);
		_edges.push_back(std::pair<int, int>(v, w));
	}

	inputFile.close();

	Graph* _graph = new Graph(_uniqueVerts.size());

	for (auto& edge : _edges)
	{
		_graph->addEdge(edge.first, edge.second);
	}

	if (_graphSize)
		*_graphSize = _uniqueVerts.size();

	return _graph;
}
