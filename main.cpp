#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>





bool readFromFile(std::string path, Graph &graph)
{
    std::ifstream file;
    file.open(path);

    if(!file.is_open())
        return false;

    bool readVertex = true;
    bool isDirected = false;
    std::string line;

    while(file.good())
    {
        if(readVertex) //first section
        {
            std::getline(file, line, '\n'); 
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
    return true;
}

int main(int argc, char *argv[])
{
    if(argc == 4)
    {
        Graph graph;
        if(readFromFile(argv[1], graph))
        {
            graph.shortestPath(argv[2], argv[3]); 
            std::cout << "Success: output.txt was created att your working directory." << std::endl;
        }
        else
        {
            std::cerr << "Error: Invalid path: ";
            std::cerr << argv[1] << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Invalid arguments." << std::endl;
        std::cout << "Please enter the following arguments: \nExecutable    path-to-read    startpoint    endpoint" << std::endl;
    }
        
}   