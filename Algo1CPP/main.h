#include "graph.h"

bool BFS(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
bool GreedyMethod(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents);
int FordFulkerson(Graph &newGraph, int s, int t, bool (*FlowFindingFunction)(Graph &graph, int s, int t, vector<int> &capacities, vector<int> &parents));
void PrintMinCut(Graph &newGraph, int s, int t);
int getParamsFromUser(Graph &g, int &s, int &t);