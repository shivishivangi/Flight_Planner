#pragma once

#include <map>
#include <unordered_map>
#include "edge.h"
#include "parse_data.h"
#include "graph.h"
#include "routes.h"
#include "cs225/PNG.h"

class Flights {
    public:
    std::map<std::string, std::pair<double, double>> vertex_coordinates; //map of airport IATAs to their latitude, longitude pair.
    std::map<Route, double, RouteCompare> edge_path; //map of routes to their distances.
    Graph world; //graph that we are constructing all the airports and their distances on.

    /**
     * Default constructor that inserts appropriate vertices and edges into our world graph.
     */
    Flights();

    /**
     * Destructor that deletes data
     */
    ~Flights();

    /**
     * Stores source and destination locations from user input.
     * @param userSource - a string that is the user's starting airport
     * @param userDestination - a string that is the user's destination airport
     */
    void storeUserInput(std::string userSource, std::string userDestination);

    /**
     * Uses HSLAPixel class to represent vertices on graph as pixels.
     * @return The PNG that is the newly created map.
     */
    cs225::PNG* createMap();

    /**
     * Superimposes our image with vertices on top of a world map for clearer visual representation.
     * @return The superimposed PNG.
     */
    cs225::PNG* mergeImage();

    /**
     * Colors in the route from the user source to the user's destination
     */
    void highlightIATAs();

    /**
     * Fixes x coordinate pixel to plot on visual graph
     * @param x - the x coordinate that will be rotated as well as reflected
     * @param map_layout - the visual graph of airports created in Flights
     * @return The fixed int x coordinate
     */
    int fixXPixel(int x, cs225::PNG* map_layout);

    /**
     * Fixes y coordinate pixel to plot on visual graph
     * @param y - the y coordinate that will be rotated as well as reflected
     * @param map_layout - the visual graph of airports created in Flights
     * @return The fixed int y coordinate
     */
    int fixYPixel(int y, cs225::PNG* map_layout);




    private:

    unsigned int WORLD_WIDTH = 360; //width of our map PNG
    unsigned int WORLD_HEIGHT = 180; //height of our map PNG

    AirportVertex userSrc; //user input source IATA.
    AirportVertex userDest; //user input destination IATA.
};
