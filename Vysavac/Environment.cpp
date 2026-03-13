//
// Created by adrian on 3/11/26.
//

#include "Environment.h"
#include <opencv4/opencv2//opencv.hpp>
#include <iostream>

namespace environment {

    Environment::Environment(const Config& config) : resolution(config.resolution) {
        // Načítanie obrázka v odtieňoch sivej (CV_8UC1) [cite: 16, 17]
        map = cv::imread(config.map_filename, cv::IMREAD_GRAYSCALE);

        // Ošetrenie chýb (napr. neexistujúci súbor) [cite: 15, 84]
        if (map.empty()) {
            std::cerr << "Chyba: Mapa " << config.map_filename << " sa nenasla!" << std::endl;
        }
    }

    bool Environment::isOccupied(double x, double y) const {
        if (map.empty()) return true;

        // Prepočet reálnych súradníc (metre) na pixely [cite: 28, 35]
        int px = static_cast<int>(x / resolution);
        int py = static_cast<int>(y / resolution);

        // Kontrola hraníc mapy [cite: 84]
        if (px < 0 || px >= map.cols || py < 0 || py >= map.rows) {
            return true;
        }

        // Biely pixel (255) je voľno, čierny (0) je prekážka [cite: 18]
        // Na obrázku vidíme, že steny sú čierne
        return map.at<uchar>(py, px) < 128; // < 128 berieme ako čiernu (prekážku)
    }

    double Environment::getWidth() const { return map.cols * resolution; }
    double Environment::getHeight() const { return map.rows * resolution; }

} // namespace environment