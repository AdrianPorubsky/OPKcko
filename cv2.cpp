//
// Created by adrian on 2/25/26.
//
#include "include/cv2.h"

Canvas::Canvas(int width, int height) {
    // Vytvorenie bieleho plátna [cite: 67, 75]
    image = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
}

void Canvas::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

void Canvas::clear() {
    shapes.clear(); // Vymazanie poľa tvarov [cite: 44]
}

void Canvas::show() {
    // Reset plátna na bielo pred každým vykreslením
    image = cv::Scalar(255, 255, 255);

    for (const auto& shape : shapes) {
        shape->draw(image); // Využitie polymorfizmu [cite: 194]
    }

    cv::imshow("Shape Drawer", image); // [cite: 114]
}