#include <unordered_map>
#include <iterator>
#include <iostream>
#include <vector>

#include "dijkstra.h"
using namespace std;

AirportVertex Dijkstra::minDist(unordered_map<string, int> flightDist, unordered_map<string, bool> airportsVisited, int num_vertex, vector<AirportVertex> vertices) { 

    int min = INT_MAX;
    int min_index; 
    for (int v = 0; v < num_vertex; v++) 
        if (airportsVisited[vertices[v]] == false && flightDist[vertices[v]] <= min)  {
            min = flightDist[vertices[v]];
            min_index = v; 
        }
    return vertices[min_index]; 
} 

vector<string> Dijkstra::recursivePath(unordered_map<string, string> parentMap, AirportVertex curr, vector<string> populate_path) 
{ 
      
    if (parentMap[curr] == "-1") 
        return populate_path;
    populate_path.push_back(curr);
    return recursivePath(parentMap, parentMap[curr], populate_path); 
    
    cout << curr << endl; 
} 

vector<string> Dijkstra::print(unordered_map<string, int> flightDist, int n, unordered_map<string, string> parentMap, vector<AirportVertex> vertices, AirportVertex source, AirportVertex dest, vector<string> populate_path) 
{ 

    for (int i = 1; i < n; i++) 
    { 
        if (vertices[i] == dest) {
            std::cout << "Your Flight Information: \n" << std::endl;

            cout << source << " -> " << vertices[i] << "   Total Distance: " <<  flightDist[vertices[i]]
             << "km \n" << endl;
        }
    }
    return recursivePath(parentMap, dest, populate_path); 
} 
vector<string> Dijkstra::dijkstra(Graph world, AirportVertex source, AirportVertex dest) 
{ 
	unordered_map<string, int> flightDist;
	unordered_map<string, bool> airportsVisited;
	unordered_map<string, string> parentMap;
    vector<string> populate_path;
	parentMap[source] = "-1";
	vector<AirportVertex> vertices = world.getVertices();
	int num_vertex = vertices.size();

    for (int i = 0; i < num_vertex; i++) 
    { 
        flightDist[vertices[i]] = INT_MAX; 
        airportsVisited[vertices[i]] = false; 
    }
    flightDist[source] = 0; 
    for (int count = 0; count < num_vertex - 1; count++) 
    {  
        string u = minDist(flightDist, airportsVisited, num_vertex, vertices); 
        airportsVisited[u] = true;  
        for (int v = 0; v < num_vertex; v++) {
            if (!airportsVisited[vertices[v]] && world.edgeExists(u, vertices[v])) {
                if (flightDist[u] + world.getEdgeWeight(u, vertices[v]) < flightDist[vertices[v]]) {
                    parentMap[vertices[v]] = u; 
                    flightDist[vertices[v]] = flightDist[u] + world.getEdgeWeight(u, vertices[v]); 
                }
            }
        }   
    }
    return print(flightDist, num_vertex, parentMap, vertices, source, dest, populate_path); 
    // return parentMap;
} 