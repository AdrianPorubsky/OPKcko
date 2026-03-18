#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "Geometry.h"

class Canvas {
public:
    // Konstruktor nacita mapu
    Canvas(const std::string& window_name, const std::string& map_path, double resolution);

    // Vykresli bod
    void drawPoint(const geometry::Point2d& point, const cv::Scalar& color, int radius = 5);

    // Vykresli cely sken
    void drawLidarScan(const std::vector<geometry::Point2d>& scan, const cv::Scalar& color);

    // Vykresli robota
    void drawRobot(const geometry::RobotState& state, double radius_m, const cv::Scalar& color);

    void clear();

    void show();

private:
    std::string window_name_;
    cv::Mat map_image_;      // Originalna mapa (stale biela/cierna)
    cv::Mat current_frame_;  // To, co prave kreslime (farebne)
    double resolution_;

    // Pomocna funkcia na prepocet metrov na pixely
    cv::Point toPx(const geometry::Point2d& p) const;
};