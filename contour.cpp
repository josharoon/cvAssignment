//
// Created by Josh on 06/01/2022.
//

#include <iostream>
#include "contour.h"

void contour::detect() {
    if(input.channels()!=1){cvtColor(input,tmp,COLOR_BGR2GRAY);}
        else{tmp=input.clone();}

    findContours(tmp, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);


}
void contour::draw() {
    if(input.channels()!=3)cvtColor(input,input, COLOR_GRAY2BGR);


    int _levels = 6;
    drawContours(input, contours, _levels <= 0 ? 3 : -1, Scalar(128, 255, 255),
                 3, LINE_AA, hierarchy, std::abs(_levels) );
    input.copyTo(output);

}

void contour::aproximateContours() {
    contourPoly.resize(contours.size());
    centers.resize(contours.size());
    radius.resize(contours.size());
    boundRect.resize(contours.size());
    for( size_t i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( contours[i], contourPoly[i], 3, true );
        boundRect[i] = minAreaRect( contourPoly[i] );
        minEnclosingCircle( contourPoly[i], centers[i], radius[i] );
    }



}

//we set an area threshold for the vehicles
void contour::detectVehicleEvent() {
    vehicleEvents=0;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        double area = contourArea(contours[i]);
        if(area > vehicleAreaThreshold ){
            drawEventBox(i, Scalar(0, 255, 0));
            vehicleEvents++;
        }
    }
}
void contour::detectTrainEvent() {
    trainEvents=0;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        double area = contourArea(contours[i]);
        if(area > trainAreaThreshold && boundRect[i].angle> minAngle && boundRect[i].angle < maxAngle){
            //test orientation of bounding rectangle.
            //find longest then get angle.
            Point2f rect_points[4];
            boundRect[i].points(rect_points );
            drawEventBox(i, Scalar(255, 0, 0));
            trainEvents++;
        }
    }
}
void contour::drawEventBox(size_t i, Scalar_<int> color) {
    Point2f rect_points[4];
    boundRect[i].points(rect_points );
    for ( int j = 0; j < 4; j++ )
    {
        line(output, rect_points[j], rect_points[(j + 1) % 4], color);
    }
}

[[maybe_unused]] void contour::discardContours() {

    for( size_t i = 0; i < contours.size(); i++ )
    {
        double area = contourArea(contours[i]);
        if(area < vehicleAreaThreshold){
            contours.erase(contours.begin() + i - 1);
        }
       if(i==contours.size())break;
    }

}

void contour::setAreaThreshold(int areaThreshold) {
    contour::vehicleAreaThreshold = areaThreshold;
}
int contour::getVehicleEvents() const {
    return vehicleEvents;
}
void contour::setTrainAreaThreshold(int trainAreaThreshold) {
    contour::trainAreaThreshold = trainAreaThreshold;
}

void contour::setAngleTolerance(double min, double max) {
    minAngle=min;
    maxAngle=max;
}

int contour::getTrainEvents() const {
    return trainEvents;
}
