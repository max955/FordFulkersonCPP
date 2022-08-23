#pragma once
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include <queue>
#include <list>
#include <stdexcept>
#include <vector>

using namespace std;

class Graph
{
private:
	vector<list<pair<int, int>>> _vertices;

	void destroy();
	void init(int size);

public:
	Graph(int size = 0);
	Graph(const Graph &otherGraph);

	~Graph();

	Graph &operator=(const Graph &otherGraph);
	Graph &Transpose(Graph dest);

	int GetLength() const { _vertices.size(); }
	int AddToEdgeCapacity(int u, int v, int c);

	bool IsAdjacent(int u, int v);
	bool checkBounds(int num) const;

	list<pair<int, int>> &GetAdjList(int u);

	void AddEdge(int u, int v, int c);
	void RemoveEdge(int u, int v);
	void MakeEmptyGraph();
};
