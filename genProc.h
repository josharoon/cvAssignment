//
// Created by Josh on 06/01/2022.
//

#ifndef VIDEORECODER_GENPROC_H
#define VIDEORECODER_GENPROC_H

#include <functional>
#include "absProc.h"

/**
 * generic processor class accepts an image processing function and an input image for processing
 * vertices are accepted that can describe a mask for processsing
 */

class genProc : public absProc {



public:
    /**
     * accepts multiple input images for processing
     * @param inputs a vector of image matrices
     */
    void setInputs(const std::vector<Mat> &inputs);
    /**
     * accepts an image and parameters processing
     * @param func function accepting image and vector of ints for parameters
     */
    void procFunc(std::function<Mat &(Mat &, std::vector<int>)> func);
    /**
     * as above
     * @param func function accepting image and vector of points for parameters
     */
    void procFunc(std::function<Mat &(Mat &, std::vector<Point2f>)> func);
    /**
 * as above
 * @param func function accepting 2 images and vector of points for parameters
 */
    void procFunc(std::function<Mat &(Mat &,Mat &, std::vector<int>)> func);
/**
 * accepts vector of vertices can be used for masking image processing area of function
 * @param vertices  a vector of vertices
 */

    void procFunc(std::function<Mat &(Mat &,Scalar,std::vector<Point2f>)> func);





    void setVerticies(const std::vector<Point2f> &vertices);
private:

    std::vector<Mat> inputs;
    std::vector<Point2f> verticies;
    Scalar color;
public:
    void setColor(const Scalar &color);


};






#endif //VIDEORECODER_GENPROC_H
