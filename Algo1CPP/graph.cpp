#include "graph.h"

Graph::~Graph()
{
    destroy();
}

Graph::Graph(int size)
{
    init(size);
}

Graph::Graph(const Graph &other)
{
    *this = other;
}

Graph &Graph::operator=(const Graph &otherGraph)
{
    if (this != &otherGraph)
    {
        this->destroy();

        if (otherGraph.GetLength() > 0)
        {
            this->init(otherGraph.GetLength());
            for (int index = 0; index < otherGraph.GetLength(); index++)
            {
                for (pair<int, int> edgePair : otherGraph._vertices[index])
                {
                    this->_vertices[index].push_back({edgePair.first, edgePair.second});
                }
            }
        }
    }

    return *this;
}

void Graph::destroy()
{
    for (vector<list<pair<int, int>>>::iterator vertex = _vertices.begin(); vertex != _vertices.end(); ++vertex)
    {
        vertex->clear();
    }

    this->_vertices.clear();
}

void Graph::init(int size)
{
    if (size < 0)
    {
        throw std::logic_error("Tried initializing a graph with a negative number");
    }
    else if (size > 0)
    {
        _vertices = vector<list<pair<int, int>>>(size);
    }
}

void Graph::MakeEmptyGraph()
{
    int oldLength = this->GetLength();
    this->destroy();
    this->init(oldLength);
}

bool Graph::IsAdjacent(int u, int v)
{
    bool found = false;

    if (!checkBounds(u) || !checkBounds(v))
    {
        throw std::logic_error("out of bounds - ListGraph");
    }

    for (auto vItr : _vertices[u])
    {
        found |= vItr.first == v;
    }

    return found;
}

list<pair<int, int>> &Graph::GetAdjList(int u)
{
    if (!checkBounds(u))
    {
        throw std::logic_error("out of bounds - ListGraph");
    }

    return this->_vertices[u];
}

void Graph::AddEdge(int u, int v, int capacity)
{
    if (!checkBounds(u) || !checkBounds(v))
    {
        throw std::logic_error("out of bounds - ListGraph");
    }

    if (!IsAdjacent(u, v))
    {
        this->_vertices[u].push_back({v, capacity});
    }
}

void Graph::RemoveEdge(int u, int v)
{
    if (!checkBounds(u) || !checkBounds(v))
    {
        throw std::logic_error("out of bounds - ListGraph");
    }

    auto &adjacents = this->GetAdjList(u);

    for (pair<int, int> edgePair : adjacents)
    {
        if (edgePair.first == v)
        {
            adjacents.remove(edgePair);
        }
    }
}

bool Graph::checkBounds(int num) const
{
    return num >= 0 && num < this->GetLength();
}

int Graph::AddToEdgeCapacity(int u, int v, int capacity)
{
    list<pair<int, int>> &adjacents = this->GetAdjList(u);

    for (auto edgePair = adjacents.begin(); edgePair != adjacents.end(); ++edgePair)
    {
        if (edgePair->first == v)
        {
            edgePair->second += capacity;
            return edgePair->second;
        }
    }
}