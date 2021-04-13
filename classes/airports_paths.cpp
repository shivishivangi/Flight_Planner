#ifndef AIRPORT
#define AIRPORT

#include <map>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "airports_paths.h"
#include "edge.h"
#include "routes.h"
#include "parse_data.h"
#include "graph.cpp"
#include "dijkstra.h"

using namespace cs225;

Flights::Flights() : world(true) {
    Parse p;
    edge_path = p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    
    for (std::map<Route, double, RouteCompare>::iterator it = edge_path.begin(); it != edge_path.end(); ++it) {
        AirportVertex source = it->first.getSrc();
        AirportVertex destination = it->first.getDes();
        double weight = it->second;

        if (!world.vertexExists(source)) {
            world.insertVertex(source);
        }
        if (!world.vertexExists(destination)) {
            world.insertVertex(destination);
        }

        Edge e(source, destination, weight, "");
        world.insertEdge(e.source, e.dest);
        world.setEdgeWeight(e.source, e.dest, weight);
        
    }
    vertex_coordinates = p.getIATACoordinates();
}

Flights::~Flights() {
    delete this;
}

void Flights::storeUserInput(std::string userSource,std::string userDestination) {
    AirportVertex s(userSource);
    AirportVertex d(userDestination);
    userSrc = s;
    userDest = d;
}

//this function graphs the airportVertexes.
cs225::PNG* Flights::createMap() {
    cs225::PNG* map_layout = new PNG(WORLD_WIDTH, WORLD_HEIGHT);

    for (std::map<std::string, std::pair<double, double>>::iterator it = vertex_coordinates.begin();
     it != vertex_coordinates.end(); ++it) {
         unsigned int x_coord = it->second.second + 180;
         unsigned int y_coord = it->second.first + 90;

         if (x_coord < WORLD_WIDTH && y_coord < WORLD_HEIGHT) {
            HSLAPixel & p = map_layout->getPixel(x_coord, y_coord);
            p.l = 0;
         }
    }

    cs225::PNG* rotated_image = new cs225::PNG(map_layout->width(), map_layout->height());

    for (unsigned int x = 0; x < map_layout->width(); x++) {
        for (unsigned int y = 0; y < map_layout->height(); y++) {
            int pixel_x = (map_layout->width() - x) - 1;
            int pixel_y = (map_layout->height() - y) - 1;
            
            cs225::HSLAPixel & rotated_pixel = map_layout->getPixel(pixel_x, pixel_y);
            rotated_image->getPixel(x, y) = rotated_pixel;
        }
    
    }
    delete map_layout;

    

    cs225::PNG* reflected_image = new cs225::PNG(rotated_image->width(), rotated_image->height());

    for (int x = 0; x < (int)rotated_image->width(); x++) {
            for (int y = 0; y < (int) rotated_image->height(); y++) {
                int pixel_x = (rotated_image->width() - x);

                cs225::HSLAPixel & r_pixel = rotated_image->getPixel(pixel_x, y);

                reflected_image->getPixel(x, y) = r_pixel;
            }
    }
    delete rotated_image;
    return reflected_image;
}


cs225::PNG* Flights::mergeImage() {

    cs225::PNG* map_image = new cs225::PNG(WORLD_WIDTH, WORLD_HEIGHT);
    cs225::PNG* png = createMap();
    map_image->readFromFile("data/grey_map.png");

    for (unsigned int x = 0; x < map_image->width(); x++ ) {
      for (unsigned int y = 0; y < map_image->height(); y++) {
        HSLAPixel &top = png->getPixel(x, y);
        HSLAPixel &base = map_image->getPixel(x, y);
        if (top.l == 0.0) {
            base.h = 1;
            base.s = 0;
            base.l = 1.0;
            base.a = 1;
        }
      }
    }
    return map_image;
}



//iterate through the coordinates.
//create a pixel that highlights that coordinate

void Flights::highlightIATAs() {
    cs225::PNG* map_layout = mergeImage();

    Dijkstra d;
    std::vector<std::string> string_v = d.dijkstra(world, userSrc, userDest);
    string_v.push_back(userSrc);
    std::reverse(string_v.begin(), string_v.end());

    for (size_t x = 0; x < string_v.size(); x++) {
        AirportVertex v(string_v[x]);
        int x_fix = fixXPixel(vertex_coordinates[v].second + 180, map_layout);
        int y_fix = fixYPixel(vertex_coordinates[v].first + 90, map_layout);
        HSLAPixel &p = map_layout->getPixel(x_fix, y_fix);
        if (x == 0) {
            p.h = 126;
            p.s = 1.0;
            p.l = 0.56;
            p.a = 1;
        }   else if (x == string_v.size() - 1) {
            p.h = 0;
            p.s = 1.0;
            p.l = 0.56;
            p.a = 1;
        }   else {
            p.h = 62;
            p.s = 1.0;
            p.l = 0.50;
            p.a = 1;
        }
        for (int i = x_fix - 2; i <= x_fix + 2; i++) {
            for (int j = y_fix - 2; j <= y_fix + 2; j++) {
            HSLAPixel &src_pix = map_layout->getPixel(i, j);
                src_pix.h = p.h;
                src_pix.s = p.s;
                src_pix.l = p.l;
                src_pix.a = p.a;
            }
        }

    }
    map_layout->writeToFile("shortest_path.png");
    delete map_layout;
}

int Flights::fixXPixel(int x, cs225::PNG* map_layout) {
    
    unsigned int x_c = map_layout->width() - ((map_layout->width() - x) - 1) ;

    return x_c;
}

int Flights::fixYPixel(int y, cs225::PNG* map_layout) {

    unsigned int y_c = (map_layout->height() - y) - 1;
    return y_c;
}

#endif /* AIRPORT */