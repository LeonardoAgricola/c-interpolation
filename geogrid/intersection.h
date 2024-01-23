#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <vector>
#include "../geometry.h"

class LineIntersection
{
public:
    /**
     * @brief Calculates the intersection point of two lines.
     * @param l1p1 First point of line 1.
     * @param l1p2 Second point of line 1.
     * @param l2p1 First point of line 2.
     * @param l2p2 Second point of line 2.
     * @return Intersection point or Point2D(0, 0) if lines are parallel.
     */
    static Point2D GetIntersectionPoint(const Point2D &l1p1, const Point2D &l1p2, const Point2D &l2p1, const Point2D &l2p2)
    {
        // Coefficients of the equation representing the lines: A*x + B*y = C
        double A1 = l1p2.Y - l1p1.Y;
        double B1 = l1p1.X - l1p2.X;
        double C1 = A1 * l1p1.X + B1 * l1p1.Y;

        double A2 = l2p2.Y - l2p1.Y;
        double B2 = l2p1.X - l2p2.X;
        double C2 = A2 * l2p1.X + B2 * l2p1.Y;

        // Determinant of the coefficient matrix
        double det = A1 * B2 - A2 * B1;
        const double epsilon = 1e-10;

        if (std::abs(det) < epsilon)
        {
            return Point2D(0, 0); // Lines are parallel
        }
        else
        {
            // Calculate intersection point
            double x = (B2 * C1 - B1 * C2) / det;
            double y = (A1 * C2 - A2 * C1) / det;

            // Check if intersection point lies on both line segments
            bool online1 = ((std::min(l1p1.X, l1p2.X) < x || std::abs(std::min(l1p1.X, l1p2.X) - x) < epsilon) &&
                            (std::max(l1p1.X, l1p2.X) > x || std::abs(std::max(l1p1.X, l1p2.X) - x) < epsilon) &&
                            (std::min(l1p1.Y, l1p2.Y) < y || std::abs(std::min(l1p1.Y, l1p2.Y) - y) < epsilon) &&
                            (std::max(l1p1.Y, l1p2.Y) > y || std::abs(std::max(l1p1.Y, l1p2.Y) - y) < epsilon));

            bool online2 = ((std::min(l2p1.X, l2p2.X) < x || std::abs(std::min(l2p1.X, l2p2.X) - x) < epsilon) &&
                            (std::max(l2p1.X, l2p2.X) > x || std::abs(std::max(l2p1.X, l2p2.X) - x) < epsilon) &&
                            (std::min(l2p1.Y, l2p2.Y) < y || std::abs(std::min(l2p1.Y, l2p2.Y) - y) < epsilon) &&
                            (std::max(l2p1.Y, l2p2.Y) > y || std::abs(std::max(l2p1.Y, l2p2.Y) - y) < epsilon));

            if (online1 && online2)
                return Point2D(x, y); // Intersection point is valid
            else
                return Point2D(0, 0); // Intersection point lies outside one or both line segments
        }
    }
};

class IntersectionPoints
{
public:
    /**
     * @brief Finds intersection points between a line and a convex polygon.
     * @param l1p1 First point of the line.
     * @param l1p2 Second point of the line.
     * @param poly Convex polygon to check for intersections.
     * @return Vector of intersection points.
     */
    static std::vector<Point2D> GetIntersectionPoints(const Point2D &l1p1, const Point2D &l1p2, const ConvexPolygon2D &poly)
    {
        std::vector<Point2D> intersectionPoints;

        for (size_t i = 0; i < poly.Corners.size(); i++)
        {
            size_t next = (i + 1 == poly.Corners.size()) ? 0 : i + 1;

            Point2D ip = LineIntersection::GetIntersectionPoint(l1p1, l1p2, poly.Corners[i], poly.Corners[next]);

            // Check if the intersection point is valid (not at the origin)
            if (!GeometryHelper::IsEqual(ip.X, 0.0) && !GeometryHelper::IsEqual(ip.Y, 0.0))
            {
                intersectionPoints.push_back(ip);
            }
        }
        return intersectionPoints;
    }
};

#endif
