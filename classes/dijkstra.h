#pragma once
#include "airports_paths.h"
#include "parse_data.h"
#include "graph.h"
#include "edge.h"


class Dijkstra
{
	public:
		/**
		 *  This is the helper function for Dijkstra's algorithm which returns the AirportVertex
		 *  that is closest to the current vertex. Also checks whether the AirportVertex being probed currently
		 *  has been visited beforehand
		 * @param dist - A map containing the shortest distances of every vertex relative to the source
		 * @param airportsVisited - A map containing IATA codes and boolean values which are true if the Vertex has been visited before and false otherwise
		 * @param num_vertex - total number of vertices in the graph
		 * @param vertices - A vector containing all of the AirportVertices 
		 */
		AirportVertex minDist(unordered_map<string, int> dist, unordered_map<string, bool> airportsVisited, int num_vertex, vector<AirportVertex> vertices);
		/**
		 * Recursive helper function that displays the flight path from source to destination
		 * @param parent - Map of all the Airport Vertices in the shortest path and their parent Vertices
		 * @param j - The destination AirportVertex
		 * @param populate_path - keeps track of the path taken
		 * @return a string vector of the airport IATAs of the shortest flight path determined (in order from dest to source)
		 */
		vector<string> recursivePath(unordered_map<string, string> parent, AirportVertex j, vector<string> populate_path);
		/**
		 * prints out the final flight path taken 
		 * @param dist - A map containing the shortest distances of every vertex relative to the source
		 * @param n - total number of vertices in the graph
		 * @param parent - Map of all the Airport Vertices in the shortest path and their parent Vertices
		 * @param vertices - A vector containing all of the AirportVertices
		 * @param source - the inputted source airport
		 * @param dest - the inputted destination 
		 * @return string vector containing the IATAs of shortest possible flight path 
		 */
		vector<string> print(unordered_map<string, int> dist, int n, unordered_map<string, string> parent, vector<AirportVertex> vertices, AirportVertex source, AirportVertex dest, vector<string> populate_path);
		/**
		 * Implementation of Dijkstra's algorithm which uses BFS to find the shortest path between a source and destination vertex.
		 * It uses a map with IATA values as keys and distances of every other vertex from the source as values.
		 * It also contains another map which stores the required flight path relative to the current vertex,
		 * as well as a map which keeps track of visited vertices.
		 * @param world - the graph of airports created in Flights
		 * @param source - the inputted source airport
		 * @param dest - the inputted destination 
		 * @return string vector containing the IATAs of shortest possible flight path 
		 */
		vector<string> dijkstra(Graph world, AirportVertex source, AirportVertex dest);


	private:

};
