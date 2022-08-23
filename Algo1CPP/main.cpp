#include "graph.h"

using namespace std;

bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
bool Dijkstra(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents));
void PrintMinCut(Graph &newGraph, int s, int t);
int getParamsFromUser(Graph &g, int &s, int &t);
void ReprioritizeQueue(priority_queue<pair<int, int>> &q);

int main(int argc, char const *argv[])
{
    int s, t, errCode;
    Graph myGraph = Graph(), extraGraph = Graph();
    errCode = getParamsFromUser(myGraph, s, t);
    if (!errCode)
    {
        extraGraph = myGraph;
        printf("BFS Method:\nMax flow: %d\n", FordFulkerson(extraGraph, s, t, &BFS));
        PrintMinCut(extraGraph, s, t);

        extraGraph = myGraph;
        printf("Greedy Method:\nMax flow: %d\n", FordFulkerson(myGraph, s - 1, t - 1, &Dijkstra));
        PrintMinCut(myGraph,  extraGraph, s);

        return 0;
    }

    return errCode;
}

int getParamsFromUser(Graph &g, int &s, int &t)
{
    int size = -1, edges = -1, edgeSide1, edgeSide2, capacity;
    scanf("%d", &size);

    if (size < 1)
    {
        printf("invalid input");
        return 1;
    }

    g = Graph(size);

    scanf("%d", &edges);

    if (edges < 1)
    {
        printf("invalid input");
        return 2;
    }

    scanf("%d", &s);

    if (!g.checkBounds(--s))
    {
        printf("invalid input");
        return 3;
    }
    scanf("%d", &t);

    if (!g.checkBounds(--t))
    {
        printf("invalid input");
        return 3;
    }

    while (edges--)
    {
        scanf("%d %d %d", &edgeSide1, &edgeSide2, &capacity);

        if (!g.checkBounds(--edgeSide1) || !g.checkBounds(--edgeSide2))
        {
            printf("invalid input");
            return 3;
        }

        if (capacity < 1)
        {
            printf("invalid input");
            return 2;
        }

        g.AddEdge(edgeSide1, edgeSide2, capacity);
    }

    return 0;
}

bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
{
    queue<int> q;
    int u;
    capacities = vector<int>(graph.GetLength(), -1);
    parents = vector<int>(graph.GetLength(), -1);

    q.push(s);
    capacities[s] = 0;

    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (pair<int, int> e : graph.GetAdjList(u))
        {
            if (capacities[e.first] < 0 && e.second > 0)
            {
                q.push(e.first);
                parents[e.first] = u;
                capacities[e.first] = e.second;
            }
        }
    }

    return capacities[t] > 0;
}

bool Dijkstra(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
{
    priority_queue<pair<int, int>> q;
    capacities = vector<int>(graph.GetLength(), -1);
    parents = vector<int>(graph.GetLength(), -1);
    capacities[s] = 0;

    for (int i = 0; i < capacities.size(); i++)
    {
        q.emplace(i, capacities[i]);
    }

    while (!q.empty())
    {
        pair<int, const int &> u = q.top();
        q.pop();

        for (pair<int, int> e : graph.GetAdjList(u.first))
        {
            if (capacities[e.first] < e.second)
            {
                parents[e.first] = u.first;
                capacities[e.first] = e.second;
            }
        }
        // TODO: Reprioritize Queue
        // ReprioritizeQueue(q);
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
    int path_flow = INT8_MAX;

    while (FlowFindingFunction(newGraph, s, t, capacities, parents))
    {
        for (v = t; v != s; v = parents[v])
        {
            path_flow = min(path_flow, capacities[v]);
        }

        for (v = t; v != s; v = parents[v])
        {
            u = parents[v];
            newGraph.AddToEdgeCapacity(u, v, (-path_flow));
        }

        max_flow += path_flow;
        path_flow = INT8_MAX;
    }

    return max_flow;
}

void PrintMinCut(Graph &newGraph, int s, int t)
{
    vector<int> capacities, parents1, parents2;
    vector<bool> visited(newGraph.GetLength(), false);
    Graph tGraph;
    BFS(newGraph, s, s, capacities, parents1);

    printf("Min cut: S =");

    for (int i = 0; i < parents1.size(); i++)
    {
        if (i == s || (parents1[i] != -1 && i != t))
        {
            printf(" %d", i + 1);
        }
    }

    printf(". T =");

    for (int i = 0; i < parents1.size(); i++)
    {
        if (i != s && (parents1[i] == -1 || i == t))
        {
            printf(" %d", i + 1);
        }
    }
}