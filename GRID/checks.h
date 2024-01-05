#ifndef CHECKS_H
#define CHECKS_H

#include "geometry.h"
#include <vector>

/**
 * Checks if a point is inside a polygon using the ray-casting algorithm.
 *
 * @param point The point to check.
 * @param polygon The polygon represented by a vector of points.
 * @return True if the point is inside the polygon, false otherwise.
 */
bool isPointInsidePolygon(const Point &point, const std::vector<Point> &polygon)
{
    int n = polygon.size();
    int count = 0;

    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        // Check if the point is on the right side of the edge and within the edge's y-range
        if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
            (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x))
        {
            count++;
        }
    }

    // If the count of intersections with polygon edges is odd, the point is inside the polygon
    return count % 2 == 1;
}

/**
 * Checks if a given point is present in a vector of points.
 *
 * @param point The point to check.
 * @param polygon The vector of points to search for the given point.
 * @return True if the point is found in the vector, false otherwise.
 */
bool isPointInVector(const Point &point, const std::vector<Point> &polygon)
{
    for (const Point &vertex : polygon)
    {
        // Check if the coordinates of the given point match any vertex in the vector
        if (point.x == vertex.x && point.y == vertex.y)
        {
            return true;
        }
    }

    // The point was not found in the vector
    return false;
}

#endif