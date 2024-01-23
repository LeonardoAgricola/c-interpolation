#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <string>
#include "../limits/boundbox.h"
#include "../limits/wkt.h"
#include "../geometry.h"
#include "../geogrid/checks.h"
#include "../geogrid/intersection.h"
#include <fstream>
#include <sstream>


std::string pointToWKT(const Point& point) {
    std::ostringstream oss;
    oss << point.x << " " << point.y;
    return oss.str();
}




std::vector<Point> creatGrid(const std::string &wkt, const double &size)
{

    Polygon geometries = wktToCoordinates(wkt);

    std::vector<double> limits = calculateBoundingBox(geometries);

    double xbegin = limits[0];
    double xend = limits[1];
    double ybegin = limits[2];
    double yend = limits[3];

    // Crie um vetor para armazenar os dados JSON
    std::vector<std::string> jsonData;

    int countin = 0;
    int countinter = 0;

    for (double x = xbegin; x <= xend; x += size)
    {
        for (double y = ybegin; y <= yend; y += size) 
        {
            
            Point pontoA = {x, y};
            Point pontoB = {x, y + size};
            Point pontoC = {x + size, y + size};
            Point pontoD = {x + size, y};

            bool checkP1 = isPointInsidePolygon({x, y}, geometries);
            bool checkP2 = isPointInsidePolygon({x, y + size}, geometries);
            bool checkP3 = isPointInsidePolygon({x + size, y + size}, geometries);
            bool checkP4 = isPointInsidePolygon({x + size, y}, geometries);

            if (checkP1 && checkP2 && checkP3 && checkP4)
            {
                countin++;
        
                std::string wktData = "POLYGON((" + pointToWKT(pontoA) + ", "
                    + pointToWKT(pontoB) + ", "
                    + pointToWKT(pontoC) + ", "
                    + pointToWKT(pontoD) + "))";
                jsonData.push_back(wktData);

            }
            else if (checkP1 || checkP2 || checkP3 || checkP4)
            {
                countinter++;

                Polygon pixel;
                pixel.vertices = {pontoA, pontoB, pontoC, pontoD, pontoA};

                Polygon recortado = clipPolygon(pixel, geometries);

                std::string wktData = "POLYGON((" + pointToWKT(recortado.vertices[0]) + ", "
                    + pointToWKT(recortado.vertices[1]) + ", "
                    + pointToWKT(recortado.vertices[2]) + ", "
                    + pointToWKT(recortado.vertices[3]) + "))";
                jsonData.push_back(wktData);
                // allPixel.emplace_back(recortado);
            }
        }
    }

    // Salvar dados JSON em um arquivo
    std::ofstream outputFile("output.json");
    if (outputFile.is_open()) {
        for (const auto& data : jsonData) {
            outputFile << data << std::endl;
        }
        outputFile.close();
        std::cout << "Dados salvos com sucesso em output.json" << std::endl;
    }
    else {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    }

    std::cout << countin << " pixels in and " << countinter << " pixels intersecion" << std::endl;

    std::vector<Point> pixels;

    return pixels;
}

#endif