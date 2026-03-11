//
// Created by adrian on 2/25/26.
//

#ifndef UNTITLED_CV2_H
#define UNTITLED_CV2_H

#include "shapes.h"
#include <vector>
#include <memory>

class Canvas {
    cv::Mat image;
    std::vector<std::unique_ptr<Shape>> shapes; // [cite: 45]
public:
    Canvas(int width, int height);
    void addShape(std::unique_ptr<Shape> shape);
    void clear();
    void show();
};

#endif //UNTITLED_CV2_H