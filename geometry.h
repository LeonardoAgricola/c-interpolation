#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

class GeometryHelper {
public:
    static const double EqualityTolerance;

    static bool IsEqual(double d1, double d2) {
        return std::abs(d1 - d2) <= EqualityTolerance;
    }
};

const double GeometryHelper::EqualityTolerance = 0.000000001;

class Point2D {
public:
    double X;
    double Y;

    Point2D(double x, double y) : X(x), Y(y) {}
};

class ConvexPolygon2D {
public:
    std::vector<Point2D> Corners;

    ConvexPolygon2D(const std::vector<Point2D>& corners) : Corners(corners) {}
};

#endif