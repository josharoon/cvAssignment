//
// Created by Josh on 06/01/2022.
//

#ifndef VIDEORECODER_HOUGHP_H
#define VIDEORECODER_HOUGHP_H


#include "Hough.h"
#include <set>
class HoughP : public Hough {

public:
    HoughP();
    std::vector<Vec4i> linesP;
    std::vector<Vec4i> linesP2;
    std::set<std::vector<Vec4i>> outlines;

    /**
   * detect lines inimage
   */
    void detect() override;
    /**
 * draw detected lines over image
     * @param color 8bit bgr color value for lines.
     * @param lineVector vector of lines to be drawn
 */
    void draw(const Scalar_<int> &color, std::vector<Vec4i> &lineVector);
    /**
 * evaluate angle of given line
 * @param line  vector representing line
 */
    double getAngle(Vec4i line) override;
/**
 * return the length of a line
 */
    double length() override;
/**
 * validates whether detected lines meet criteria. Used for detecting barrier events
 */
    void validateLines();
/**
 * return an integer number of detected events
 */
    int getEvents();
/**
 * set parameters used in detection of hough lines
 */
    void setParams(const std::vector<int> &params);
   /**
    * return outout image matrix with lines detected lines drawn on it.
    */

    Mat& getOutput();

private:
    std::vector<int> params;
};


#endif //VIDEORECODER_HOUGHP_H
