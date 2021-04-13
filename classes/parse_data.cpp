#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cmath>
#include <utility>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include "parse_data.h"
#include "edge.h"
#include "stdc++.h"
#include "routes.h"

using namespace std;

std::map<Route, double, RouteCompare> Parse::parseData(const string& airports, const string& routes) {
    string line;

    ifstream infile(routes);
    
    if (infile.is_open()) {
        int rows = 1; 
        int column = 1;

        while (getline(infile, line)) { 
            string sourceIATA = "";
            AirportVertex source = "";
            AirportVertex dest = "";
            string destinationIATA = "";
            string delimiter = ",";
            size_t charCount = 0;
            int commaCount = 0; 

            while ((charCount = line.find(delimiter)) != std::string::npos) {
                commaCount++;

                if (commaCount == SOURCE_AIRPORT_COL - 1) {
                    column = SOURCE_AIRPORT_COL;
                } else if (commaCount == DESTINATION_AIRPORT_COL - 1) {
                    column = DESTINATION_AIRPORT_COL; 
                } else {
                    column = 0;
                }
                
                if (column == SOURCE_AIRPORT_COL) {
                    sourceIATA = line.substr(0, charCount);
                    source = sourceIATA; 
                }
                if (column == DESTINATION_AIRPORT_COL) {
                    destinationIATA = line.substr(0, charCount);
                    dest = destinationIATA; 
                }
                
                if (source != "" && dest != "") {
                    Route route(source, dest);

                    airline_routes.push_back(route);
                    break;
                }

                line.erase(0, charCount + delimiter.length());
            }
            rows++;
        }
    }
    infile.close();
    parseAirlines(airports);
    createRouteDistance();
    return paths;
}


void Parse::parseAirlines(const string& airports) {
    string line;

    ifstream infile(airports);
    
    if (infile.is_open()) {
        int rows = 1; 
        int column = 1;

        while (getline(infile, line)) { 
            string codeIATA; 
            double airline_latitude = 0.0; 
            double airline_longitude = 0.0;
            string delimiter = ",";
            size_t charCount = 0;
            int commaCount = 0; 

            while ((charCount = line.find(delimiter)) != std::string::npos) {
                commaCount++;

                std::string curr = line.substr(0, charCount);
                int quoteCount = 0;
                for (size_t i = 0; i < curr.size(); i++) {
                    if (curr.at(i) == '"') {
                        quoteCount++;
                    }
                }
                if (quoteCount % 2 != 0) {
                    commaCount--;
                }

                if (commaCount == AIRLINE_IATA_COL - 1) {
                    column = AIRLINE_IATA_COL; 
                } else if (commaCount == LATITUDE_COL - 1) {
                    column = LATITUDE_COL;
                } else if (commaCount == LONGITUDE_COL - 1) {
                    column = LONGITUDE_COL; 
                } else {
                    column = 0;
                }

                if (column == AIRLINE_IATA_COL) {
                    std::string s = line.substr(1, charCount - 2);
                    codeIATA = line.substr(1, charCount - 2);
                }
                if (column == LATITUDE_COL) {
                    std::string str_lat = line.substr(0, charCount);
                    airline_latitude = std::stod(str_lat);
                }
                if (column == LONGITUDE_COL) {
                    std::string str_long = line.substr(0, charCount);
                    airline_longitude = std::stod(str_long);
                }

                std::pair<double, double> lat_long;
                lat_long = std::make_pair(airline_latitude, airline_longitude);
                //if (codeIATA.size() == 3) {
                    coordinates[codeIATA] = lat_long;
                //}
                line.erase(0, charCount + delimiter.length());
            }
            rows++;
        }
    }
    infile.close();
}

void Parse::createRouteDistance()  {
    for (auto x : airline_routes) {
        double src_lat = coordinates[x.getSrc()].first;
        double src_long = coordinates[x.getSrc()].second;
        double dest_lat = coordinates[x.getDes()].first; 
        double dest_long = coordinates[x.getDes()].second;

        double distance = findDistance(src_lat, src_long, dest_lat, dest_long);

        paths.insert(std::pair<Route, double>(x, distance));
    }
}



double Parse::toRadians(double deg) {
    double one_deg = (M_PI) / 180; 
    return (one_deg * deg); 
} 

double Parse::findDistance(double srcLat, double srcLong, double destLat, double destLong) {
    srcLat = toRadians(srcLat); 
    srcLong = toRadians(srcLong); 
    destLat = toRadians(destLat); 
    destLong = toRadians(destLong); 
      

    double long_dif = destLong - srcLong; 
    double lat_dif = destLat - srcLat; 
  
    double distance = pow(sin(lat_dif / 2), 2) +  
                          cos(srcLat) * cos(destLat) *  
                          pow(sin(long_dif / 2), 2); 
  
    distance = 2 * asin(sqrt(distance)); 
  
 
    double R = 6371; 

    distance = distance * R; 
  
    return distance; 
}

bool Parse::isProperResponse(const std::string& userSource, const std::string& userDestination) {
    bool proper_src = false;
    bool proper_dest = false;
    if (userSource.size() != 3 || userDestination.size() != 3) {
        return false;
    }
    if (coordinates.find(userSource) != coordinates.end()) {
        proper_src = true;
    }

    if (coordinates.find(userDestination) != coordinates.end()) {
        proper_dest = true;
    }

    if (proper_src && proper_dest) {
        return true;
    }
    return false;
}
std::map<std::string, std::pair<double, double>> Parse::getIATACoordinates() {
    return coordinates;
}
