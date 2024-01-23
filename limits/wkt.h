#ifndef WKT_H
#define WKT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../geometry.h"

/**
 * @brief Converts Well-Known Text (WKT) polygon to a vector of coordinates (points).
 * 
 * This function extracts coordinates from the WKT representation and stores them in a vector.
 * 
 * @param wkt The Well-Known Text representation of a polygon.
 * @return A vector of points representing the coordinates of the polygon.
 */
Polygon wktToCoordinates(const std::string &wkt)
{
    // Create a vector to store the coordinates (points) of the polygon
    Polygon coordinates;

    // Find the start and end positions of the coordinate information in the WKT
    size_t start = wkt.find("(") + 2;
    size_t end = wkt.find(")");

    // Use iterators to avoid unnecessary string copies
    std::istringstream iss(wkt.substr(start, end - start));
    std::string token;

    // Count the number of commas to determine the required capacity
    size_t commaCount = std::count(wkt.begin(), wkt.end(), ',') + 1;
    coordinates.vertices.reserve(commaCount / 2 + 1);

    // Tokenize the cleaned WKT and extract individual points
    while (std::getline(iss, token, ','))
    {
        // Create a Point structure to store x and y coordinates
        Point vertex;

        // Use another stringstream to extract x and y values from the token
        std::istringstream pointStream(token);
        pointStream >> vertex.x >> vertex.y;

        // Add the vertex to the vector of coordinates
        coordinates.vertices.emplace_back(vertex);
    }

    // Return the vector of coordinates representing the polygon
    return coordinates;
}

#endif
