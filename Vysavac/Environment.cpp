//
// Created by adrian on 3/11/26.
//

#include "Environment.h"
#include <opencv4/opencv2//opencv.hpp>
#include <iostream>

namespace environment {

    Environment::Environment(const Config& config) : resolution(config.resolution) {
        map = cv::imread(config.map_filename, cv::IMREAD_GRAYSCALE);

        // subor neni
        if (map.empty()) {
            std::cerr << "Chyba: Mapa " << config.map_filename << " sa nenasla!" << std::endl;
        }
    }

    bool Environment::isOccupied(double x, double y) const {
        if (map.empty()) return true;

        // Suradnice na metre
        int px = static_cast<int>(x / resolution);
        int py = static_cast<int>(y / resolution);

        // Hranice mapy
        if (px < 0 || px >= map.cols || py < 0 || py >= map.rows) {
            return true;
        }

        return map.at<uchar>(py, px) < 128; // cierna = prekazka
    }

    double Environment::getWidth() const { return map.cols * resolution; }
    double Environment::getHeight() const { return map.rows * resolution; }

} // namespace environment