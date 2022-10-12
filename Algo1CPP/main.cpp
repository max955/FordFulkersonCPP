#include "main.h"

int main(int argc, char const *argv[])
{
    int s, t, errCode;
    Graph mainGraph, extraGraph;
    errCode = getParamsFromUser(mainGraph, s, t);
    if (!errCode)
    {
        extraGraph = mainGraph;
        printf("BFS Method:\nMax flow: %d\n", FordFulkerson(extraGraph, s, t, &BFS));
        PrintMinCut(extraGraph, s, t);

        extraGraph = mainGraph;
        printf("\nGreedy Method:\nMax flow: %d\n", FordFulkerson(extraGraph, s, t, &GreedyMethod));
        PrintMinCut(extraGraph, s, t);

        return 0;
    }

    return errCode;
}

int getParamsFromUser(Graph &graph, int &s, int &t)
{
    int size = -1, edges = -1, edgeSide1, edgeSide2, capacity;
    scanf("%d", &size);

    if (size < 1)
    {
        printf("invalid input");
        return 1;
    }

    graph = Graph(size);

    scanf("%d", &edges);

    if (edges < 1)
    {
        printf("invalid input");
        return 2;
    }

    scanf("%d", &s);

    if (!graph.checkBounds(--s))
    {
        printf("invalid input");
        return 3;
    }
    scanf("%d", &t);

    if (!graph.checkBounds(--t))
    {
        printf("invalid input");
        return 3;
    }

    while (edges--)
    {
        scanf("%d %d %d", &edgeSide1, &edgeSide2, &capacity);

        if (!graph.checkBounds(--edgeSide1) || !graph.checkBounds(--edgeSide2))
        {
            printf("invalid input");
            return 3;
        }

        if (capacity < 1)
        {
            printf("invalid input");
            return 2;
        }

        graph.AddEdge(edgeSide1, edgeSide2, capacity);
    }

    return 0;
}


bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
{
    queue<int> nodeQueue;
    int currentNode;
    capacities = vector<int>(graph.GetLength(), -1);
    parents = vector<int>(graph.GetLength(), -1);
    capacities[s] = 0;

    nodeQueue.emplace(s);

    while (!nodeQueue.empty())
    {
        currentNode = nodeQueue.front();
        nodeQueue.pop();
        for (pair<int, int> edge : graph.GetAdjList(currentNode))
        {
            if (parents[edge.first] == -1 && edge.second > 0)
            {
                parents[edge.first] = currentNode;
                capacities[edge.first] = edge.second;
                nodeQueue.emplace(edge.first);
            }
        }
    }

    return capacities[t] > 0;
}

bool GreedyMethod(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents)
{
    priority_queue<pair<int, int>> nodePriorityQueue;
    int currentNode;
    capacities = vector<int>(graph.GetLength(), -1);
    parents = vector<int>(graph.GetLength(), -1);
    capacities[s] = 0;

    nodePriorityQueue.emplace(make_pair(capacities[s], s));

    while (!nodePriorityQueue.empty())
    {
        currentNode = nodePriorityQueue.top().second;
        nodePriorityQueue.pop();
        for (pair<int, int> edge : graph.GetAdjList(currentNode))
        {
            if (capacities[edge.first] < edge.second && 0 < edge.second && parents[edge.first] < 0)
            {
                capacities[edge.first] = edge.second;
                parents[edge.first] = currentNode;
                nodePriorityQueue.emplace(make_pair(capacities[edge.first], edge.first));
            }
        }
    }

    return capacities[t] > 0;
}

int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents))
{
    vector<int> capacities, parents;
    int currentNode, max_flow = 0, path_flow = INT8_MAX;

    while (FlowFindingFunction(newGraph, s, t, capacities, parents))
    {
        for (currentNode = t; currentNode != s && currentNode >= 0 && parents[currentNode] >= 0; currentNode = parents[currentNode])
        {
            path_flow = min(path_flow, capacities[currentNode]);
        }

        for (currentNode = t; currentNode != s; currentNode = parents[currentNode])
        {
            newGraph.AddToEdgeCapacity(parents[currentNode], currentNode, (-path_flow));
        }

        max_flow += path_flow;
        path_flow = INT8_MAX;
    }

    return max_flow;
}

void PrintMinCut(Graph &newGraph, int s, int t)
{
    vector<int> capacities, parents;
    vector<bool> visited(newGraph.GetLength(), false);

    BFS(newGraph, s, s, capacities, parents);

    printf("Min cut: S =");

    for (int i = 0; i < parents.size(); i++)
    {
        if (i == s || (parents[i] != -1 && i != t))
        {
            printf(" %d", i + 1);
        }
    }

    printf(". T =");

    for (int i = 0; i < parents.size(); i++)
    {
        if (i != s && (parents[i] == -1 || i == t))
        {
            printf(" %d", i + 1);
        }
    }
}