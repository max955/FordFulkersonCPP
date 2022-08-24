#include "graph.h"

bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
bool Dijkstra(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents));
void PrintMinCut(Graph &newGraph, int s, int t);
int getParamsFromUser(Graph &g, int &s, int &t);
void ReprioritizeQueue(priority_queue<pair<int, int>> &q);