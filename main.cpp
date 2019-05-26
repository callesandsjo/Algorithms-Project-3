#include "Graph.h"
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc == 3)
    {
        std::ifstream file;
        file.open(argv[1]);
        if(!file.is_open())
        {
            std::cerr << "Error: Invalid path: ";
            std::cerr << argv[1] << std::endl;
        }
        else
        {
            //input
            bool readVertex = true;
            bool isDirected = false;
            std::string line;
            std::getline(file, line, '\n'); 
            if(line == "DIRECTED")
                isDirected = true;
            
            Graph graph(isDirected);
             while(file.good())
            {
                if(readVertex) //first section
                {
                    std::getline(file, line, '\n'); 
                    if(line == "")
                        readVertex = false;
                    else
                        graph.addVertex(line);
                }
                else //second section
                {
                    std::string fromVertex;
                    std::string toVertex;
                    unsigned int weight;
                    std::getline(file, line, '\t');
                    fromVertex = line;
                    std::getline(file, line, '\t');
                    toVertex = line;
                    std::getline(file, line, '\n');
                    std::stringstream(line) >> weight;
                    graph.addEdge(fromVertex, toVertex, weight);
                }
            }
            file.close();

            //shortest path
            std::string argument = argv[2];
            std::string from = "";
            std::string to = "";
            bool readFirstNode = true;
            for(auto character: argument)
            {
                if(character == '-')
                    readFirstNode = false;
                else if(readFirstNode)
                    from += character;
                else
                    to += character;
            }

            if(graph.shortestPath(from, to)) //outputing to txt file in working directory
                std::cout << "Success: Answer.txt has been created at the executable directory." << std::endl; 
            else
                std::cerr << "Error: an error occured while getting shortest path. Does the vertices exist and/or are they connected?" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Invalid arguments." << std::endl;
        std::cout << "Please enter the following arguments: \n.\Executable    path-to-read    startpoint-endpoint" << std::endl;
    }
    return 0;
}   