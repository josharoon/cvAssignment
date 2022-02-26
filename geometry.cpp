//
// Created by sutclj2 on 14/12/2021.
//

#include "geometry.h"

const Point &geometry::getA() const {
    return a;
}

void geometry::setA(const Point &a) {
    geometry::a = a;
}

const Point &geometry::getB() const {
    return b;
}

void geometry::setB(const Point &b) {
    geometry::b = b;
}

double geometry::getDistance() {

    geometry::setDistance(norm(getA()-getB()))   ;

    return distance;
}

void geometry::setDistance(double distance) {
    geometry::distance = distance;
}

