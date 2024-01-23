#ifndef BOUNDBOX_H
#define BOUNDBOX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "../geometry.h"

/**
 * @brief Calculates the minimum and maximum coordinates from a vector of points.
 * @param geometry Vector of Point representing the geometry.
 * @return Vector of doubles containing {minx, maxx, miny, maxy}.
 */
std::vector<double> calculateBoundingBox(const Polygon& geometry) {
    // Initialize the coordinates vector
    std::vector<double> coords;

    // Set initial min and max values using the first vertex
    double minx = geometry.vertices[0].x, maxx = geometry.vertices[0].x;
    double miny = geometry.vertices[0].y, maxy = geometry.vertices[0].y;

    // Iterate through the array using references
    for (const auto& vertex : geometry.vertices) {
        minx = (vertex.x < minx) ? vertex.x : minx;
        maxx = (vertex.x > maxx) ? vertex.x : maxx;
        miny = (vertex.y < miny) ? vertex.y : miny;
        maxy = (vertex.y > maxy) ? vertex.y : maxy;
    }

    // Add the calculated values to the coords vector
    coords.emplace_back(minx);
    coords.emplace_back(maxx);
    coords.emplace_back(miny);
    coords.emplace_back(maxy);

    return coords;
}

#endif