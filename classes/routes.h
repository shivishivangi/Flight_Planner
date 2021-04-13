#pragma once

#include <iostream>
#include <functional>
#include "edge.h"

class Route {
public:
    /**
     * Default constructor for Route class.
     */
    Route() : src(""), des("") {}

    /**
     * Creates a Route with specific source and destination.
     */
    Route(AirportVertex s, AirportVertex d) : src(s), des(d) {}

    /**
     * Sets source location of a route to some AirportVertex value.
     */
    void setSrc(AirportVertex s) {
        src = s;
    }

    /**
     * Sets destination location of a route to some AirportVertex value.
     */
    void setDes(AirportVertex d) {
        des = d;
    }

    /**
     * Retrieves source of a certain route.
     * @return The AirportVertex, which is the source location.
     */
    AirportVertex getSrc() const {
        return src;
    }

    /**
     * Retrieves destination of a certain route.
     * @return The AirportVertex, which is the destination location.
     */
    AirportVertex getDes() const {
        return des;
    }

    /**
     * Compares two routes.
     * @return true, if they are equal.
     */
    bool operator==(const Route& other) const {
        return (this->getSrc() == other.getSrc() &&
        this->getDes() == other.getDes());
    }

private:

    AirportVertex src; //Source airport in route.
    AirportVertex des; //Destination airport in route.
};

/**
 * Struct created for the purpose of lexicographic order in the map, by source.
 */
struct RouteCompare {
   bool operator() (const Route& lhs, const Route& rhs) const {
       if (lhs.getSrc() != rhs.getSrc()) {
        return lhs.getSrc() < rhs.getSrc();
       } else {
           return lhs.getDes() < rhs.getDes();
       }
   }
};