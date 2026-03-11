#ifndef SHAPES_H
#define SHAPES_H

#include <opencv2/opencv.hpp>

// Základná trieda - abstraktná [cite: 167, 171]
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw(cv::Mat& image) = 0; // Abstraktná metóda [cite: 174]
};

// Odvodená trieda Circle [cite: 176, 178]
class Circle : public Shape {
private:
    cv::Point center;
    int radius;
    cv::Scalar color;
public:
    Circle(cv::Point c, int r, cv::Scalar col) : center(c), radius(r), color(col) {}
    void draw(cv::Mat& image) override; // Implementácia v .cpp [cite: 179, 180]
};

// Odvodená trieda Rectangle [cite: 183, 185]
class Rectangle : public Shape {
private:
    cv::Point topLeft, bottomRight;
    cv::Scalar color;
public:
    Rectangle(cv::Point p1, cv::Point p2, cv::Scalar col) : topLeft(p1), bottomRight(p2), color(col) {}
    void draw(cv::Mat& image) override; // Implementácia v .cpp [cite: 186, 187]
};

#endif