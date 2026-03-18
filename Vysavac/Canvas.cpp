//
// Created by adrian on 3/17/26.
//

#include "Canvas.h"

Canvas::Canvas(const std::string& window_name, const std::string& map_path, double resolution)
    : window_name_(window_name), resolution_(resolution) {
    map_image_ = cv::imread(map_path, cv::IMREAD_COLOR);
    if (map_image_.empty()) {
        std::cerr << "Canvas Error: Could not load map at " << map_path << std::endl;
    }
    clear(); // Inicializuje current_frame_
}

void Canvas::clear() {
    map_image_.copyTo(current_frame_);
}

cv::Point Canvas::toPx(const geometry::Point2d& p) const {
    return cv::Point(static_cast<int>(p.x / resolution_),
                     static_cast<int>(p.y / resolution_));
}

void Canvas::drawPoint(const geometry::Point2d& point, const cv::Scalar& color, int radius) {
    cv::circle(current_frame_, toPx(point), radius, color, -1);
}

void Canvas::drawLidarScan(const std::vector<geometry::Point2d>& scan, const cv::Scalar& color) {
    for (const auto& pt : scan) {
        cv::circle(current_frame_, toPx(pt), 1, color, -1);
    }
}

void Canvas::drawRobot(const geometry::RobotState& state, double radius_m, const cv::Scalar& color) {
    cv::Point center = toPx({state.x, state.y});
    int radius_px = static_cast<int>(radius_m / resolution_);

    // Telo robota
    cv::circle(current_frame_, center, radius_px, color, 2);

    // Smerovka (heading)
    cv::Point heading_end(
        center.x + (radius_px + 5) * std::cos(state.theta),
        center.y + (radius_px + 5) * std::sin(state.theta)
    );
    cv::line(current_frame_, center, heading_end, cv::Scalar(255, 0, 0), 2);
}

void Canvas::show() {
    cv::imshow(window_name_, current_frame_);
}