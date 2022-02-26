//
// Created by Josh on 06/01/2022.
//

#ifndef VIDEORECODER_EDGEGEO_H
#define VIDEORECODER_EDGEGEO_H


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
using namespace cv;
class edgeGeo {

public:
    void setInput(const cv::Mat &input);

    const cv::Mat &getOutput() const;

    virtual void detect()=0;

    virtual void draw()=0;


    Mat input;
    Mat tmp;
    Mat output;
};


#endif //VIDEORECODER_EDGEGEO_H
