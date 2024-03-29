#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <limits>
#include <fstream>


class Graph
{
    private:
        struct Vertex
        {
            std::string name;
            unsigned int distanceFromStart;
            Vertex* previousVertex;
            std::vector<std::pair<unsigned int, Vertex*>> edges; //weight, next vertex
            bool isVisited;        
        };
        struct compareDistance{
            bool operator()(Vertex* const& v1, Vertex* const& v2) { return v1->distanceFromStart > v2->distanceFromStart;}
        };
    private:
        const unsigned int infinity = std::numeric_limits<unsigned int>::max();
        bool isDirected;
        std::vector<Vertex*> graphVector;
        void shortestPathRecursive(std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> &priorityQueue, Vertex* endVertex);
        bool outputShortestPath(Vertex* startVertex, Vertex* endVertex) const;
        Vertex* findVertex(std::string vertexName);
    public:
        Graph(bool isDirected);
        void addVertex(std::string name);
        void addEdge(std::string startName, std::string endName, unsigned int weight);
        bool shortestPath(std::string startName, std::string endName);
        ~Graph();
};

Graph::Graph(bool isDirected)
    : isDirected(isDirected) {}

void Graph::addVertex(std::string name)
{
    Vertex *newVertex = new Vertex;
    newVertex->name = name;
    newVertex->previousVertex = nullptr;
    newVertex->distanceFromStart = infinity;
    newVertex->isVisited = false;
    this->graphVector.push_back(newVertex); 
}

Graph::Vertex* Graph::findVertex(std::string vertexName)
{
    for(auto &v: this->graphVector)
    {
        if(v->name == vertexName)
            return v;
    }
    return nullptr;
}

void Graph::addEdge(std::string startName, std::string endName, unsigned int weight)
{
    Vertex* startVertex = findVertex(startName);
    Vertex* endVertex = findVertex(endName);

    
    if(!this->isDirected)
        endVertex->edges.push_back(std::make_pair(weight, startVertex));
    startVertex->edges.push_back(std::make_pair(weight, endVertex));
}

bool Graph::shortestPath(std::string startName, std::string endName)
{
    
    Vertex* startVertex = findVertex(startName);
    Vertex* endVertex = findVertex(endName);
    

    std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> priorityQueue;
    startVertex->distanceFromStart = 0;

    priorityQueue.push(startVertex);

    shortestPathRecursive(priorityQueue, endVertex);
    if(startVertex == nullptr || endVertex == nullptr || !outputShortestPath(startVertex, endVertex))
        return false;
    return true;
}    

void Graph::shortestPathRecursive(std::priority_queue<Vertex*, std::vector<Vertex*>, compareDistance> &priorityQueue, Vertex *endVertex)
{

    if(priorityQueue.top() == endVertex || priorityQueue.empty()) //searching until shortest path to endVertex is found or entire graph has been searched (in case startNode and endNode isnt connected)
        return;

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
    shortestPathRecursive(priorityQueue, endVertex);
}

bool Graph::outputShortestPath(Vertex* startVertex, Vertex* endVertex) const
{
    unsigned int distance = endVertex->distanceFromStart;
    std::ofstream file;
    std::string vertexPath = "";
    while(endVertex->previousVertex != nullptr)
    {
        vertexPath = "->" + endVertex->name + vertexPath;
        endVertex = endVertex->previousVertex;
    }
    vertexPath = endVertex->name + vertexPath;
    file.open("Answer.txt");
    if(startVertex != endVertex || !file.is_open()) //startVertex and endVertex is not connected
        return false;

    file << "0" << std::endl;
    file << distance << std::endl;
    file << vertexPath << std::endl;
    file.close();
    return true;
}

Graph::~Graph()
{
    for(auto &vertex: this->graphVector)
    {
        delete vertex;
    }
}

#endif