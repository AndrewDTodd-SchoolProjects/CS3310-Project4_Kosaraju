#include "Graph.h"

#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <sstream>

Graph::Graph(const int& numVerts) : m_numVerts(numVerts)
{
	m_adjacencyLists = new std::vector<std::vector<int>*>(m_numVerts);
	for (int i = 0; i < m_numVerts; i++)
	{
		m_adjacencyLists->at(i) = new std::vector<int>();
	}
}
Graph::~Graph()
{
	for (int i = 0; i < m_numVerts; i++)
	{
		delete m_adjacencyLists->at(i);
	}
	delete m_adjacencyLists;
}

void Graph::getPositions(const int& startVert, std::vector<bool>& vertVisited, std::stack<int>& posStack)
{
	vertVisited[startVert] = true;

	for (auto i = m_adjacencyLists->at(startVert)->begin(); i != m_adjacencyLists->at(startVert)->end(); i++)
	{
		if (!vertVisited[*i])
			getPositions(*i, vertVisited, posStack);
	}

	//All verts reachable from startVert are processed. Push startVert onto posStack
	posStack.push(startVert);
}

void Graph::DFS(const int& startVert, std::vector<bool>& vertVisited, std::vector<int>* const& path, std::vector<std::vector<int>*>* const& _adjLists)
{
	vertVisited[startVert] = true;
	path->push_back(startVert);

	for (auto i = _adjLists->at(startVert)->begin(); i != _adjLists->at(startVert)->end(); i++)
	{
		if (!vertVisited[*i])
			DFS(*i, vertVisited, path, _adjLists);
	}
}

void Graph::addEdge(const int& vertOne, const int& vertTwo)
{
	m_adjacencyLists->at(vertOne - 1)->push_back(vertTwo - 1);
}

void Graph::getTransposeAdjList(std::vector<std::vector<int>*>* const& adjList)
{
	for (int vert = 0; vert < m_numVerts; vert++)
	{
		//Recur on all adjacent verts
		for (auto i = m_adjacencyLists->at(vert)->begin(); i != m_adjacencyLists->at(vert)->end(); i++)
		{
			//reverse the edge direction by swapping the vertices
			(*adjList)[*i]->push_back(vert);
		}
	}
}

void Graph::getSCCs(std::vector<std::vector<int>*>* const& sccList)
{
	std::stack<int> _stack;

	//Mark all vertices as not visited for first pass of DFS
	std::vector<bool> _vertVisited(m_numVerts, false);

	//Populate the _stack with the ordereing of the verts from first pass of DFS in getPositions
	for (int i = 0; i < m_numVerts; i++)
	{
		if (!_vertVisited[i])
			getPositions(i, _vertVisited, _stack);
	}

	std::vector<std::vector<int>*>* _transposeAdjList = new std::vector<std::vector<int>*>(m_numVerts);
	for (int i = 0; i < m_numVerts; i++)
	{
		_transposeAdjList->at(i) = new std::vector<int>();
	}
	getTransposeAdjList(_transposeAdjList);

	//Mark all verts as not visited for the second pass of DFS
	for (int i = 0; i < m_numVerts; i++)
		_vertVisited[i] = false;

	//Process the verticies with DFS in order specified on the _stack to get strongly connected components
	while (!_stack.empty())
	{
		int vert = _stack.top();
		_stack.pop();

		if (!_vertVisited[vert])
		{
			std::vector<int>* _component = new std::vector<int>;

			Graph::DFS(vert, _vertVisited, _component, _transposeAdjList);

			sccList->push_back(_component);
		}
	}

	for (int i = 0; i < m_numVerts; i++)
	{
		delete _transposeAdjList->at(i);
	}
	delete _transposeAdjList;
}