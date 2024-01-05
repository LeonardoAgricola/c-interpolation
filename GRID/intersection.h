#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <cmath>
#include <omp.h>
#include "geometry.h"
#include <vector>

// Define the structure Point with two double attributes x and y


/**
 * @brief Identify if two lines intersect.
 *
 * This function extracts the point of intersection if two vector lines intersect.
 *
 * @param p1 begin point of the first line.
 * @param q1 end point of the first line.
 * @param p2 begin point of the second line.
 * @param q2 end point of the second line.
 * @param intersection point intersection of two lines.
 * @return A boolean indicating whether the lines intersect.
 */
bool areLinesIntersecting(const Point &p1, const Point &q1, const Point &p2, const Point &q2, Point &intersection)
{
    // Coordinates of the points of the lines
    double x1 = p1.x, y1 = p1.y;
    double x2 = q1.x, y2 = q1.y;
    double x3 = p2.x, y3 = p2.y;
    double x4 = q2.x, y4 = q2.y;

    // Calculate denominator
    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    // Check if the denominator is close to zero to avoid division by zero
    if (std::abs(den) < 1e-9)
    {
        return false;
    }

    // Calculate the parameter t for the first line and the parameter u for the second line
    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    // Check if the lines intersect at a valid point (t >= 0 && t <= 1) and (u >= 0 && u <= 1)
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
        // Calculate the coordinates of the intersection point
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Finds intersection points between a given line and a set of line segments.
 *
 * @param line The line for which intersections are to be found.
 * @param upgeo The set of line segments to check for intersections.
 * @return A vector containing intersection points.
 */
std::vector<Point> getIntersection(const std::vector<Point> &line, const std::vector<Point> &upgeo)
{
    const int n = upgeo.size();
    std::vector<Point> intersections;

    #pragma omp parallel for
    for (int i = 0; i < (n - 1); ++i)
    {
        Point intersection;
        bool check = areLinesIntersecting(line[0], line[1], upgeo[i], upgeo[i + 1], intersection);

        #pragma omp critical
        if (check)
        {
            intersections.push_back(intersection);
        }
    }

    return intersections;
}

#endif // INTERSECTION_H