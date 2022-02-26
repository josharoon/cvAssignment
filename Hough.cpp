//
// Created by Josh on 05/01/2022.
//

#include "Hough.h"
#include "HoughP.h"

void Hough::detect() {
    HoughLines( input, lines, 1, CV_PI/180, 150, 0, 0 );

}

void Hough::draw() {
//not implemented
}

double Hough::getAngle(Vec4i line) {
    return 0;
}

double Hough::length() {
    return 0;
}
