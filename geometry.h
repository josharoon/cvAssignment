//
// Created by sutclj2 on 14/12/2021.
//

#ifndef VIDEORECODER_GEOMETRY_H
#define VIDEORECODER_GEOMETRY_H


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;

class geometry {
public:
    const Point &getA() const;

    void setA(const Point &a);

    const Point &getB() const;

    void setB(const Point &b);

    double getDistance();

private:
public:
    void setDistance(double distance);

private:
    Point a {0,0};
    Point b {0,0};
    double distance;

};


#endif //VIDEORECODER_GEOMETRY_H
