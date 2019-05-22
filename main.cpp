#include "TestGraph.h"
#include <fstream>
#include <sstream>
#include <iostream>





int readFromFile(std::string path, Graph &graph)
{
    std::ifstream file;
    file.open(path);

    if(!file.is_open())
        return -1;

    bool readVertex = true;
    bool isDirected = false;
    std::string line;

    while(file.good())
    {
        if(readVertex) //first section
        {
            std::getline(file, line, '\n'); //wheter it's directed or not
            //std::cout << line << std::endl;
            if(line == "DIRECTED")
                isDirected = true;
            else if(line == "UNDIRECTED")
                isDirected = false;
            else if(line == "")
                readVertex = false;
            else
            {
                graph.addVertex(line);
            }
        }
        else //second section
        {
            std::string fromVertex;
            std::string toVertex;
            unsigned int weight;
            std::getline(file, line, '\t');
            //std::cout << line << std::endl;
            fromVertex = line;
            std::getline(file, line, '\t');
            //std::cout << line << std::endl;
            toVertex = line;
            std::getline(file, line, '\n');
            //std::cout << line << std::endl;
            std::stringstream(line) >> weight;
            graph.addEdge(fromVertex, toVertex, weight, isDirected);
        }
    }
    file.close();
    return 0;
}

void outputToFile(std::string information, std::string path)
{
    std::ofstream file;
    file.open(path);


}

int main(int argc, char *argv[])
{
    Graph graph;
    readFromFile(argv[1], graph);
    std::cout << graph.shortestPath(argv[2], argv[3]) << std::endl;
    //std::cout << graph.dijkstras(argv[2], argv[3]) << std::endl;
}   