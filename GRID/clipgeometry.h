#ifndef CLIPGEOMETRY_H
#define CLIPGEOMETRY_H

#include <vector>
#include "geometry.h"
#include "intersection.h"
#include "checks.h"

/**
 * Clips a polygon represented by 'toclip' against another polygon 'geometries'.
 * Returns the clipped polygon.
 *
 * @param toclip The polygon to be clipped.
 * @param geometries The clipping polygon.
 * @return The clipped polygon.
 */
std::vector<Point> clipPolygon(const std::vector<Point> &toclip, const std::vector<Point> &geometries)
{
    std::vector<Point> clippedPolygon;
    std::vector<Point> intersections;

    auto addPointToClipped = [&clippedPolygon](const Point &point) {
        if (!isPointInVector(point, clippedPolygon)) {
            clippedPolygon.emplace_back(point);
        }
    };

    auto calculateAndAddIntersections = [&intersections, &geometries, &addPointToClipped](const Point &p1, const Point &p2) {
        intersections = getIntersection({p1, p2}, geometries);
        for (Point &intersection : intersections) {
            addPointToClipped(std::move(intersection));
        }
    };

    // Iterate through the vertices
    auto it = toclip.begin();
    const auto end = toclip.end();
    for (; it != end; ++it)
    {
        const Point &currentVertex1 = *it;
        const Point &currentVertex2 = *(it + 1);

        // Check if both vertices are inside the clipping polygon and the current vertex is not already added
        if (isPointInsidePolygon(currentVertex1, geometries) && isPointInsidePolygon(currentVertex2, geometries)) {
            addPointToClipped(currentVertex1);
        }
        else
        {
            // If the current vertex is inside the clipping polygon and not already added
            if (isPointInsidePolygon(currentVertex1, geometries)) {
                addPointToClipped(currentVertex1);
            }

            // Calculate intersections between the current edge and the clipping polygon
            calculateAndAddIntersections(currentVertex1, currentVertex2);
        }
    }

    // Add vertices from the clipping polygon that are inside the polygon to be clipped
    for (const Point &vertex : geometries)
    {
        if (isPointInsidePolygon(vertex, toclip)) {
            addPointToClipped(vertex);
        }
    }

    // Close the clipped polygon by adding the first point at the end
    clippedPolygon.emplace_back(clippedPolygon[0]);

    return clippedPolygon;
}

#endif