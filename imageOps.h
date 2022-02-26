//
// Created by Josh on 12/01/2022.
//

#ifndef VIDEORECODER_IMAGEOPS_H
#define VIDEORECODER_IMAGEOPS_H


#include <functional>
#include "absProc.h"

/**
 * static class of functions used in image processing. They provide function to the genProc
 * class to implement various image processing algorithms
 */

class imageOps {

public:
    [[maybe_unused]] static Mat &multiplyColor(Mat &inMat, std::vector<int> params);

    [[maybe_unused]]  static Mat &DivideColor(Mat &inMat, std::vector<int> params);
    /**
     * Gaussian blur on image
     * @param inMat image Matrix to apply blur to
     * @param params vector of parameters to be passed into function
     */
    static Mat &GausBlur(Mat &inMat, std::vector<int> params);
    /**
 * Morphology function for Open operation on image
 * @param inMat image Matrix to apply function to
 * @param params vector of parameters to be passed into function
 */
    static Mat &Open(Mat &inMat, std::vector<int> params);
    /**
 * Morphology function for Close operation on image
 * @param inMat image Matrix to apply function to
 * @param params vector of parameters to be passed into function
 */

    static Mat &Close(Mat &inMat, std::vector<int> params);

    /**
 * Canny edge detector
 * @param inMat image Matrix to apply function to
 * @param params vector of parameters to be passed into function
 */
    static Mat &canny(Mat &inMat, std::vector<int> params);
    /**
 * absDifference of two images
 * @param inMat image Matrix to apply function to
 * @param inMat2 image Matrix to apply function to
 * @param params vector of parameters to be passed into function
 */
    static Mat &absDiff(Mat &inMat, Mat &inMat2, std::vector<int> params);

    [[maybe_unused]] static Mat &adapThreshold(Mat &inMat,  std::vector<int> params);

    /**
     * Basic Thresholding of image
     *  @param inMat image Matrix to apply function to
     *  @param params vector of parameters to be passed into function
     */
    static Mat &basicThreshold(Mat &inMat,  std::vector<int> params);
    /**
     * set Zone for detection on image
     *  @param inMat image Matrix to apply function to
     *  @param params vector of points describing the zone.
     */
    static Mat &setZone(Mat &inMat, std::vector<Point2f> params);

    static Mat &colorZone(Mat &inMat, Scalar color, std::vector<Point2f> params);




};


#endif //VIDEORECODER_IMAGEOPS_H
