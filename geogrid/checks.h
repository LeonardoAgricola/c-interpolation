#ifndef CHECKS_H
#define CHECKS_H

#include "../geometry.h"
#include <vector>
#include <cmath>

class PointInsidePoly {
public:
    /**
     * @brief Checks if a point is inside a convex polygon.
     * @param test Point to check.
     * @param poly Convex polygon to test against.
     * @return True if the point is inside the polygon, false otherwise.
     */
    static bool IsPointInsidePoly(const Point2D& test, const ConvexPolygon2D& poly) {
        bool result = false;
        for (auto i = poly.Corners.begin(), j = std::prev(poly.Corners.end()); i != poly.Corners.end(); j = i++) {
            // Ray-casting algorithm
            if ((i->Y > test.Y) != (j->Y > test.Y) &&
                (test.X < (j->X - i->X) * (test.Y - i->Y) / (j->Y - i->Y) + i->X)) {
                result = !result;
            }
        }
        return result;
    }
};

class PointSet {
public:
    std::vector<Point2D> points;

    /**
     * @brief Adds new points to the set, avoiding duplicates.
     * @param newpoints Vector of points to add.
     */
    void AddPoints(const std::vector<Point2D>& newpoints) {
        for (const Point2D& np : newpoints) {
            // Check for duplicates before adding
            bool found = false;
            for (const Point2D& p : points) {
                if (GeometryHelper::IsEqual(p.X, np.X) && GeometryHelper::IsEqual(p.Y, np.Y)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                points.push_back(np);
            }
        }
    }
};

/**
 * @brief Compares two points based on their polar angles with respect to a center point.
 * @param a First point.
 * @param b Second point.
 * @param center Center point for angle calculations.
 * @return True if point 'a' has a smaller polar angle than point 'b' with respect to the center, false otherwise.
 */
bool ComparePoints(const Point2D& a, const Point2D& b, const Point2D& center) {
    return std::atan2(a.Y - center.Y, a.X - center.X) < std::atan2(b.Y - center.Y, b.X - center.X);
}

/**
 * @brief Orders a vector of points in a clockwise direction around their centroid.
 * @param points Vector of points to be ordered.
 */
void OrderClockwise(std::vector<Point2D>& points) {
    double mX = 0;
    double mY = 0;

    // Calculate centroid
    for (const Point2D& p : points) {
        mX += p.X;
        mY += p.Y;
    }

    mX /= points.size();
    mY /= points.size();

    // Sort points based on polar angles around the centroid
    std::sort(points.begin(), points.end(), [mX, mY](const Point2D& a, const Point2D& b) {
        return ComparePoints(a, b, Point2D(mX, mY));
    });
}

#endif
