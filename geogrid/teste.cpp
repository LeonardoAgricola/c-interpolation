#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../geometry.h"
#include "intersection.h"
#include "checks.h"



ConvexPolygon2D GetIntersectionOfPolygons(const ConvexPolygon2D& poly1, const ConvexPolygon2D& poly2) {
    std::vector<Point2D> clippedCorners;

    // Adiciona os vértices de poly1 que estão dentro de poly2
    for (const Point2D& corner : poly1.Corners) {
        if (PointInsidePoly::IsPointInsidePoly(corner, poly2))
            clippedCorners.push_back(corner);
    }

    // Adiciona os vértices de poly2 que estão dentro de poly1
    for (const Point2D& corner : poly2.Corners) {
        if (PointInsidePoly::IsPointInsidePoly(corner, poly1))
            clippedCorners.push_back(corner);
    }

    // Adiciona os pontos de interseção
    for (size_t i = 0, next = 1; i < poly1.Corners.size(); i++, next = (i + 1 == poly1.Corners.size()) ? 0 : i + 1) {
        std::vector<Point2D> intersectionPoints = IntersectionPoints::GetIntersectionPoints(poly1.Corners[i], poly1.Corners[next], poly2);
        clippedCorners.insert(clippedCorners.end(), intersectionPoints.begin(), intersectionPoints.end());
    }

    // Ordena os vértices no sentido horário
    OrderClockwise(clippedCorners);

    return ConvexPolygon2D(clippedCorners);
}


int main() {
    // Example usage
    std::vector<Point2D> corners1 = {Point2D(5.0, 1.0), Point2D(3.0, 3.0), Point2D(4.0, 8.0), Point2D(5.0, 6.0), Point2D(5.0, 1.0)};
    std::vector<Point2D> corners2 = {Point2D(3.5, 3.0), Point2D(4.0, 3.0), Point2D(4.0, 4.0), Point2D(3.5, 4.0), Point2D(3.5, 3.0)};

    ConvexPolygon2D poly1(corners1);
    ConvexPolygon2D poly2(corners2);

    ConvexPolygon2D intersectionPoly = GetIntersectionOfPolygons(poly1, poly2);

    // Process or display the intersection polygon's corners
    for (const Point2D& corner : intersectionPoly.Corners) {
        std::cout << "Corner: X = " << corner.X << ", Y = " << corner.Y << std::endl;
    }

    return 0;
}
