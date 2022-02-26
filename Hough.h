//
// Created by Josh on 05/01/2022.
//

#ifndef VIDEORECODER_HOUGH_H
#define VIDEORECODER_HOUGH_H
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include "edgeGeo.h"

using namespace cv;
/**
 * class for detection visualisation and interpretation of hough lines
 */
class Hough : public edgeGeo {

public:
    /**
     * detect lines image
     */
    virtual void detect();
/**
 * draw detected lines over image
 */
    virtual void draw();
/**
 * NOT IMPLEMENTED  evaluate angle of given line
 * @param line  vector representing line
 */
    virtual double getAngle(Vec4i line);
/**
 * NOT IMLEMENTED return the length of a line
 */
    virtual double length();
private:
    std::vector<Vec2f> lines;


};


#endif //VIDEORECODER_HOUGH_H
