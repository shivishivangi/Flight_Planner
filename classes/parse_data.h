#pragma once

#include <string>
#include <utility>
#include <unordered_map>
#include <map>
#include <vector>
#include "edge.h"
#include "routes.h"

// This class is mainly used to parse through both of our .csv files and arrange this information in data structures for future usage.
class Parse {
    public:
        std::vector<Route> airline_routes; //vector of all possible routes derived from .csv files
        std::map<std::string, std::pair<double, double>> coordinates; //map of airport IATAs to their latitude, longitude pair
        std::map<Route, double, RouteCompare> paths; //map of routes to their distances

        /**
         * Parses though routes.dat csv file and creates a vector of routes, as well as paths map.
         * @param airports - the airports data to parse through
         * @param routes - the routes data to parse through
         * @return Map that has keys as routes and values as distances.
         */
        std::map<Route, double, RouteCompare> parseData(const std::string& airports, const std::string& routes);

        /**
         * Parses through airports.csv file and creates a map of coordinates, where each airport IATA is matched to it's
         * latitude and longitude pair.
         * @param airports - the airports data to parse through
         */
        void parseAirlines(const string& airports);

        /**
         * Evaluates distance of a route using helper functions and places this value with the respective key in paths map.
         */
        void createRouteDistance();

        /**
         * Convertes degree measurement to radians measurement.
         * @param deg - degree measurement
         * @return Radians measurement.
         */
        double toRadians(double deg);

        /**
         * Calculates distance between the coordinates of two locations.
         * @param srcLat - source airport latitude
         * @param srcLong - source airport longitude
         * @param destLat - destination airport latitude
         * @param destLong - destination airport longitude
         * @return Evaluated distance.
         */
        double findDistance(double srcLat, double srcLong, double destLat, double destLong);

        /**
         * Checks validity of user input.
         * @param userSource - the user's input source airport
         * @param userDestination - the user's input destination airport
         * @return True, if user input is valid.
         */
        bool isProperResponse(const std::string& userSource, const std::string& userDestination);

        /**
         * Retrieves coordinates map.
         * @return Coordinates map.
         */
        std::map<std::string, std::pair<double, double>> getIATACoordinates();

    private:
        int SOURCE_AIRPORT_COL = 4; //column number to get source airport IATA in routes.dat.
        int DESTINATION_AIRPORT_COL = 6; //column number to get destination airport IATA in routes.dat.
        int LATITUDE_COL = 8; //column number to get a latitude in airports.dat.
        int LONGITUDE_COL = 9; //column number to get a longitude in airports.dat.
        int AIRLINE_IATA_COL = 6; //column number to get an airport IATA in airports.dat.
};

