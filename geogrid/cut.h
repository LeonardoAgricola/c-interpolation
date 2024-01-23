#ifndef CUT_H
#define CUT_H

#include <vector>
#include "../geometry.h"
#include "intersection.h"
#include "checks.h"

/**
 * @brief Clips one convex polygon against another.
 * @param poly1 First convex polygon.
 * @param poly2 Second convex polygon.
 * @return Clipped convex polygon resulting from the intersection of poly1 and poly2.
 */
ConvexPolygon2D ClipPolygons(const ConvexPolygon2D& poly1, const ConvexPolygon2D& poly2) {
    std::vector<Point2D> clippedCorners;  // Stores the clipped corners of the resulting polygon

    // Add vertices of poly1 that are inside poly2
    for (const Point2D& corner : poly1.Corners) {
        if (PointInsidePoly::IsPointInsidePoly(corner, poly2))
            clippedCorners.push_back(corner);
    }

    // Add vertices of poly2 that are inside poly1
    for (const Point2D& corner : poly2.Corners) {
        if (PointInsidePoly::IsPointInsidePoly(corner, poly1))
            clippedCorners.push_back(corner);
    }

    // Add intersection points of edges of poly1 with poly2
    for (size_t i = 0, next = 1; i < poly1.Corners.size(); i++, next = (i + 1 == poly1.Corners.size()) ? 0 : i + 1) {
        std::vector<Point2D> intersectionPoints = IntersectionPoints::GetIntersectionPoints(poly1.Corners[i], poly1.Corners[next], poly2);
        clippedCorners.insert(clippedCorners.end(), intersectionPoints.begin(), intersectionPoints.end());
    }

    // Order the vertices in a clockwise direction
    OrderClockwise(clippedCorners);

    return ConvexPolygon2D(clippedCorners);
}

#endif