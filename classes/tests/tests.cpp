#include <string>
#include <vector>
#include <utility>

#include "../catch/catch.hpp"
#include "../airports_paths.h"
#include "../dijkstra.h"

TEST_CASE("Sanity case") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Routes are being constructed properly") {
    Route r("AER", "KZN");
    REQUIRE(r.getSrc() == "AER");
    REQUIRE(r.getDes() == "KZN");
}

TEST_CASE("airports.dat is being parsed properly 1") {
    Parse p;
    p.parseAirlines("data/airports.dat.csv");
    std::pair<double, double> test_coor;
    test_coor = std::make_pair(-6.081689834590001, 145.391998291);
    REQUIRE(p.coordinates["GKA"] == test_coor);
}

TEST_CASE("airports.dat is being parsed properly 2") {
    Parse p;
    p.parseAirlines("data/airports.dat.csv");
    std::pair<double, double> test_coor;
    test_coor = std::make_pair(6.78082990646,47.45470047);
    REQUIRE(p.coordinates["GLK"] == test_coor);
}

TEST_CASE("airports.dat is being parsed properly 3") {
    Parse p;
    p.parseAirlines("data/airports.dat.csv");
    std::pair<double, double> test_coor;
    test_coor = std::make_pair(31.535499572753906,-84.19450378417969);
    REQUIRE(p.coordinates["ABY"] == test_coor);
}

TEST_CASE("routes.dat is being parsed properly 1") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    Route r("AER", "KZN");
    std::map<Route, double, RouteCompare>::iterator it = p.paths.find(r);
    double dist = p.findDistance(p.coordinates[r.getSrc()].first, p.coordinates[r.getSrc()].second,
    p.coordinates[r.getDes()].first, p.coordinates[r.getDes()].second);
    REQUIRE(p.paths[r] == dist);
}

TEST_CASE("routes.dat is being parsed properly 2") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    Route r("DEN", "PIR");
    std::map<Route, double, RouteCompare>::iterator it = p.paths.find(r);
    double dist = p.findDistance(p.coordinates[r.getSrc()].first, p.coordinates[r.getSrc()].second,
    p.coordinates[r.getDes()].first, p.coordinates[r.getDes()].second);
    REQUIRE(p.paths[r] == dist);
}

TEST_CASE("routes.dat is being parsed properly 3") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    Route r("ASF", "KZN");
    std::map<Route, double, RouteCompare>::iterator it = p.paths.find(r);
    double dist = p.findDistance(p.coordinates[r.getSrc()].first, p.coordinates[r.getSrc()].second,
    p.coordinates[r.getDes()].first, p.coordinates[r.getDes()].second);
    REQUIRE(p.paths[r] == dist);
}

TEST_CASE("edge_paths can be accessed 1") {
    Parse p;
    Flights* f = new Flights();

    Route r("PEM", "CUZ");
    std::map<Route, double, RouteCompare>::iterator it = f->edge_path.find(r);

    double dist = p.findDistance(f->vertex_coordinates[r.getSrc()].first, f->vertex_coordinates[r.getSrc()].second,
    f->vertex_coordinates[r.getDes()].first, f->vertex_coordinates[r.getDes()].second);

    REQUIRE(f->edge_path[r] == dist);
}

TEST_CASE("edge_paths can be accessed 2") {
    Parse p;
    Flights* f = new Flights();

    Route r("BDS", "ZRH");
    std::map<Route, double, RouteCompare>::iterator it = f->edge_path.find(r);

    double dist = p.findDistance(f->vertex_coordinates[r.getSrc()].first, f->vertex_coordinates[r.getSrc()].second,
    f->vertex_coordinates[r.getDes()].first, f->vertex_coordinates[r.getDes()].second);

    REQUIRE(f->edge_path[r] == dist);
}


TEST_CASE("edge_paths can be accessed 3") {
    Parse p;
    Flights* f = new Flights();

    Route r("ASF", "KZN");
    std::map<Route, double, RouteCompare>::iterator it = f->edge_path.find(r);

    double dist = p.findDistance(f->vertex_coordinates[r.getSrc()].first, f->vertex_coordinates[r.getSrc()].second,
    f->vertex_coordinates[r.getDes()].first, f->vertex_coordinates[r.getDes()].second);

    REQUIRE(f->edge_path[r] == dist);
}


TEST_CASE("checking if vertex exists") {
    Flights* f = new Flights();

    Route r("ASF", "KZN");
    Route r2("BDS", "ZRH"); 

    REQUIRE (f->world.vertexExists(r.getSrc()) == true);
    REQUIRE (f->world.vertexExists(r.getDes()) == true);
    REQUIRE (f->world.vertexExists(r2.getSrc()) == true);
    REQUIRE (f->world.vertexExists(r2.getDes()) == true);
}

TEST_CASE("checking if edge exists") {
    Flights* f = new Flights();

    Route r("ASF", "KZN");
    Route r2("BDS", "ZRH");
    Route r3("RAO", "SJP");
    Route r4("JBR", "STL");

    REQUIRE (f->world.edgeExists(r.getSrc(), r.getDes()) == true);
    REQUIRE (f->world.edgeExists(r2.getSrc(), r2.getDes()) == true);
    REQUIRE (f->world.edgeExists(r3.getSrc(), r3.getDes()) == true);
    REQUIRE (f->world.edgeExists(r4.getSrc(), r4.getDes()) == true);
    REQUIRE (f->world.edgeExists(r.getSrc(), r2.getSrc()) == false);
    REQUIRE (f->world.edgeExists(r4.getSrc(), r2.getDes()) == false);
}

TEST_CASE("checking if edge weight exists") {
    Parse p;
    Flights* f = new Flights();

    Route r("ASF", "KZN");
    Route r2("BDS", "ZRH");
    Route r3("RAO", "SJP");
    Route r4("JBR", "STL");

    std::map<Route, double, RouteCompare>::iterator it = f->edge_path.find(r);
    double dist1 = p.findDistance(f->vertex_coordinates[r.getSrc()].first, f->vertex_coordinates[r.getSrc()].second,
    f->vertex_coordinates[r.getDes()].first, f->vertex_coordinates[r.getDes()].second);

    std::map<Route, double, RouteCompare>::iterator it2 = f->edge_path.find(r2);
    double dist2 = p.findDistance(f->vertex_coordinates[r2.getSrc()].first, f->vertex_coordinates[r2.getSrc()].second,
    f->vertex_coordinates[r2.getDes()].first, f->vertex_coordinates[r2.getDes()].second);

    std::map<Route, double, RouteCompare>::iterator it3 = f->edge_path.find(r3);
    double dist3 = p.findDistance(f->vertex_coordinates[r3.getSrc()].first, f->vertex_coordinates[r3.getSrc()].second,
    f->vertex_coordinates[r3.getDes()].first, f->vertex_coordinates[r3.getDes()].second);

    std::map<Route, double, RouteCompare>::iterator it4 = f->edge_path.find(r4);
    double dist4 = p.findDistance(f->vertex_coordinates[r4.getSrc()].first, f->vertex_coordinates[r4.getSrc()].second,
    f->vertex_coordinates[r4.getDes()].first, f->vertex_coordinates[r4.getDes()].second);


    REQUIRE (f->world.getEdgeWeight(r.getSrc(), r.getDes()) == dist1);
    REQUIRE (f->world.getEdgeWeight(r2.getSrc(), r2.getDes()) == dist2);
    REQUIRE (f->world.getEdgeWeight(r3.getSrc(), r3.getDes()) == dist3);
    REQUIRE (f->world.getEdgeWeight(r4.getSrc(), r4.getDes()) == dist4);

}

TEST_CASE("checking properResponses") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");

    Route r("ASF", "KZN");
    Route m("BDS", "ZRH");

    REQUIRE (p.isProperResponse(r.getSrc(), m.getSrc()) == true);
    REQUIRE (p.isProperResponse(r.getDes(), m.getDes()) == true);
    REQUIRE (p.isProperResponse("ZCY", "AYL") == false);
    REQUIRE (p.isProperResponse("AYL", "WTL") == false);
}

TEST_CASE("Checking Dijkstra 1: direct flight") {
    Flights * s = new Flights(); 
    Dijkstra d; 
    AirportVertex a("AER"); 
    AirportVertex b("KZN");
    vector<string> path = d.dijkstra(s->world, a, b); 
    path.push_back(a); 
    std::reverse(path.begin(), path.end());

    vector<string> test; 
    test.push_back("AER");
    test.push_back("KZN");

    REQUIRE(test == path);
}

TEST_CASE("Checking Dijkstra 2: non direct flight") {
    Flights * s = new Flights(); 
    Dijkstra d; 
    AirportVertex a("ORD"); 
    AirportVertex b("BLR");
    vector<string> path = d.dijkstra(s->world, a, b); 
    path.push_back(a); 
    std::reverse(path.begin(), path.end());

    vector<string> test; 
    test.push_back("ORD");
    test.push_back("DEL");
    test.push_back("BLR");

    REQUIRE(test == path);
}

TEST_CASE("Checking Dijkstra 3: LONG non direct flight") {
    Flights * s = new Flights(); 
    Dijkstra d; 
    AirportVertex a("AKL"); 
    AirportVertex b("AGP");
    vector<string> path = d.dijkstra(s->world, a, b); 
    path.push_back(a); 
    std::reverse(path.begin(), path.end());

    vector<string> test; 
    test.push_back("AKL");
    test.push_back("BKK");
    test.push_back("IST");
    test.push_back("AGP");

    REQUIRE(test == path);
}

// TEST_CASE("checking") {
//     Parse p;
//     p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
//     Flights* f = new Flights();
//     f->createMap();
//     f->mergeImage();
// }
/*
TEST_CASE("highlight IATAs") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    Flights* f = new Flights();
    f->createMap();
    f->mergeImage();
    Route r("KZN", "DME");
    f->highlightIATAs();
}
*/
/*
TEST_CASE("highlight IATAs 2") {
    Parse p;
    p.parseData("data/airports.dat.csv", "data/routes.dat.csv");
    Flights* f = new Flights();
    f->createMap();
    f->mergeImage();
    Route r("SIN", "KUL");
    f->highlightIATAs();
}
*/