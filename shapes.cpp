#include "include/shapes.h"

Circle::Circle(cv::Point c, int r, cv::Scalar col) : center(c), radius(r), color(col) {}

void Circle::draw(cv::Mat& image) {
    // Kreslenie kruhu: (obrázok, stred, polomer, farba, hrúbka) [cite: 82]
    cv::circle(image, center, radius, color, 2);
}