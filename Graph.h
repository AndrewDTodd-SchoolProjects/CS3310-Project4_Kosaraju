#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

class Graph
{
protected:
	//number of vertices in the graph
	int m_numVerts = 0;

	//pointer to a list of adjacency lists
	std::vector<std::vector<int>*>* m_adjacencyLists = nullptr;

	//Function to fill stack with the positions of the verticies computed from first pass of DFS (Topo-DFS)
	void getPositions(const int& startVert, std::vector<bool>& vertVisited, std::stack<int>& posStack);

	//A recursive DFS implementation
	static void DFS(const int& startVert, std::vector<bool>& vertVisited, std::vector<int>* const& path, std::vector<std::vector<int>*>* const& _adjLists);

public:
	Graph(const int& numVerts);
	~Graph();

	void addEdge(const int& vertOne, const int& vertTwo);

	void getTransposeAdjList(std::vector<std::vector<int>*>* const& adjList);

	void getSCCs(std::vector<std::vector<int>*>* const& sccList);
};
#endif // !GRAPH_H

