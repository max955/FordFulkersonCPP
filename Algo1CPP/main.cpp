#include "graph.h"
#include <queue>
#include <stdlib.h>
#include <math.h>

using namespace std;

namespace FordFulkerson
{

    bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
    bool Dijkstra(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
    int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents));
    void PrintMinCut(Graph &graph, Graph &newGraph, int s);

    int main(int argc, char const *argv[])
    {
        int s, t, errCode;
        Graph myGraph, extraGraph;
        pair<queue<int>, queue<int>> minCut;
        errCode = getParamsFromUser(myGraph, s, t);

        extraGraph = myGraph;
        printf("BFS Method:\nMax flow: %d\n", FordFulkerson(myGraph, s - 1, t - 1, &BFS));
        PrintMinCut(myGraph, extraGraph, s);

        extraGraph = myGraph;
        printf("Greedy Method:\nMax flow: %d\n", FordFulkerson(myGraph, s - 1, t - 1, &Dijkstra));
        PrintMinCut(myGraph,  extraGraph, s);

        return 0;
    }

    int getParamsFromUser(Graph &g, int &s, int &t)
    {
        int size = -1, edges = -1, edgeSide1, edgeSide2, capacity;

        if (size < 1)
        {
            printf("Verticeies can't be a number less than 1");
            return 1;
        }

        g = Graph(size);

        if (edges < 1)
        {
            printf("Edges can't be a number less than 1");
            return 2;
        }

        if (!g.checkBounds(s) || !g.checkBounds(t))
        {
            printf("Source or Sink are out of bounds");
            return 3;
        }

        while (edges--)
        {
            scanf("%d%d%d", edgeSide1, edgeSide2, capacity);

            if (!g.checkBounds(edgeSide1) || !g.checkBounds(edgeSide2))
            {
                printf("One or more of the provided vertecies are out of bounds");
                return 3;
            }

            if (capacity < 1)
            {
                printf("Capacity can't be a number less than 1");
                return 2;
            }

            g.AddEdge(edgeSide1, edgeSide2, capacity);
        }
    }

    bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
    {
        queue<int> q;
        int u;
        capacities = vector<int>(graph.GetLength(), 0);
        parents = vector<int>(graph.GetLength(), -1);

        q.push(s);
        capacities[s] = 0;

        while (!q.empty())
        {
            u = q.front();
            q.pop();

            for (pair<int, int> e : graph.GetAdjList(u))
            {
                if (capacities[e.first] <= 0 && e.second > 0)
                {
                    q.push(e.first);
                    parents[e.first] = u;
                    capacities[e.first] = e.second;
                }
            }
        }

        return capacities[t] < 0;
    }

    bool Dijkstra(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
    {
        priority_queue<int &> q;
        int u;
        capacities = vector<int>(graph.GetLength(), -1);
        parents = vector<int>(graph.GetLength(), -1);
        capacities[s] = INT_MAX;

        for (int i = 0; i < capacities.size(); i++)
        {
            q.emplace(capacities[i]);
        }

        while (!q.empty())
        {
            u = q.top();
            q.pop();

            for (pair<int, int> e : graph.GetAdjList(u))
            {
                if (capacities[e.first] < e.second)
                {
                    parents[e.first] = u;
                    capacities[e.first] = e.second;
                }
            }

            q.swap(q);
        }

        return capacities[t] != -1;
    }

    int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents))
    {
        int u, v;
        vector<int> capacities;
        vector<int> parents;
        int max_flow = 0;

        while (FlowFindingFunction(newGraph, s, t, parents, capacities))
        {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parents[v])
            {
                u = parents[v];
                path_flow = min(path_flow, capacities[u]);
            }

            for (v = t; v != s; v = parents[v])
            {
                u = parents[v];
                newGraph.AddToEdgeCapacity(u, v, (path_flow * (-1)));
                newGraph.AddToEdgeCapacity(v, u, path_flow);
            }

            max_flow += path_flow;
        }

        return max_flow;
    }

    void PrintMinCut(Graph &graph, Graph &newGraph, int s)
    {
        vector<int> capacities, parents1, parents2;

        BFS(graph, s, s, capacities, parents1);
        BFS(newGraph, s, s, capacities, parents2);

        printf("Min cut: S =");

        for (int i = 0; i < parents1.size(); i++)
        {
            if (parents1[i] != -1 && parents2[i] != -1)
            {
                printf(" %d", i);
            }
        }

        printf("Min cut: T =");

        for (int i = 0; i < parents1.size(); i++)
        {
            if (parents1[i] != -1 && parents2[i] == -1)
            {
                printf(" %d", i);
            }
        }
    }
}