#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <limits>

const unsigned int infinity = std::numeric_limits<unsigned int>::max();

class Graph
{
    private:
        struct Vertex
        {
            std::string name;
            unsigned int distanceFromStart;
            Vertex* previousVertex;
            std::vector<std::pair<unsigned int, Vertex*>> edges;
            bool isVisited;
            
        };
        struct compareDistance{
            bool operator()(Vertex* const& v1, Vertex* const& v2) { return v1->distanceFromStart > v2->distanceFromStart;}
        };
    private:
        std::vector<Vertex*> graphVector;
        void shortestPathRecursive(std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> &priorityQueue);
    public:
        void addVertex(std::string name);
        void addEdge(std::string startName, std::string endName, unsigned int weight, bool isDirected);
        std::string shortestPath(std::string startName, std::string endName);
        void findVertex(std::string vertexName, Vertex* &vertex);
        ~Graph();
};

void Graph::addVertex(std::string name)
{
    Vertex *newVertex = new Vertex;
    newVertex->name = name;
    newVertex->previousVertex = nullptr;
    newVertex->distanceFromStart = infinity;
    newVertex->isVisited = false;
    this->graphVector.push_back(newVertex); 
}

void Graph::findVertex(std::string vertexName, Vertex* &vertex)
{
    for(auto &v: this->graphVector)
    {
        if(v->name == vertexName)
            vertex = v;
    }
}

void Graph::addEdge(std::string startName, std::string endName, unsigned int weight, bool isDirected)
{
    Vertex* startVertex;
    Vertex* endVertex;
    findVertex(startName, startVertex);
    findVertex(endName, endVertex);
    
    if(!isDirected)
        endVertex->edges.push_back(std::make_pair(weight, startVertex));
    startVertex->edges.push_back(std::make_pair(weight, endVertex));
}

std::string Graph::shortestPath(std::string startName, std::string endName)
{
    Vertex* startVertex;
    
    findVertex(startName, startVertex);
    
    std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> priorityQueue;
    startVertex->distanceFromStart = 0;
    startVertex->isVisited = true;

    priorityQueue.push(startVertex);

    shortestPathRecursive(priorityQueue);

    std::string presentShortestPath = "";
    for(auto endVertex: this->graphVector)
    {
        presentShortestPath = std::to_string(endVertex->distanceFromStart) + presentShortestPath;
        while(endVertex != nullptr)
        {
            presentShortestPath = endVertex->name + "->" + presentShortestPath;
            endVertex = endVertex->previousVertex;
        }
        presentShortestPath = " --- " + presentShortestPath;
    }
    return presentShortestPath;
}    

void Graph::shortestPathRecursive(std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> &priorityQueue)
{

    if(priorityQueue.empty())
    {
        return;
    }

    Vertex *vertexToProcess = priorityQueue.top();
    vertexToProcess->isVisited = true;
    priorityQueue.pop();

    for(auto &nextVertex: vertexToProcess->edges)
    {
        if(!nextVertex.second->isVisited && vertexToProcess->distanceFromStart + nextVertex.first < nextVertex.second->distanceFromStart)
        {
            nextVertex.second->distanceFromStart = vertexToProcess->distanceFromStart + nextVertex.first;
            nextVertex.second->previousVertex = vertexToProcess;
            priorityQueue.push(nextVertex.second);
        }
    }
    shortestPathRecursive(priorityQueue);
}

Graph::~Graph()
{
    for(auto &vertex: this->graphVector)
    {
        delete vertex;
    }
}

#endif