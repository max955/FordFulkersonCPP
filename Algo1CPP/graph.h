#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace FordFulkerson
{

	class Graph
	{
	private:
		vector<list<pair<int, int>>> _vertices;

		void destroy();
		void init(int size);

	public:
		Graph(int size = 0);
		Graph(const Graph &other) = default;

		~Graph();

		Graph &operator=(const Graph &other) = default;

		int GetLength() const { return _vertices.size(); }
		int AddToEdgeCapacity(int u, int v, int c);

		bool IsAdjacent(int u, int v);
		bool checkBounds(int num) const;

		list<pair<int, int>> &GetAdjList(int u);

		void AddEdge(int u, int v, int c);
		void RemoveEdge(int u, int v);
		void MakeEmptyGraph();
	};
}