//
// Created by Josh on 06/01/2022.
//

#ifndef VIDEORECODER_ABSPROC_H
#define VIDEORECODER_ABSPROC_H


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>


using namespace cv;
class absProc {

public:
    const cv::Mat &getOutput() const;

    absProc() {


    }

    Mat input;
    Mat output;
    Mat inter1;
    std::vector<int> sliders;
    int count;

    void setInGrey();
    void setOutGrey();

    void setInter1(cv::Mat & in);

    const cv::Mat &getInput() const;

    void setInput(const cv::Mat &input);

    int getCount() const;

    void setCount(int count);

    void setSliders(const std::vector<int> &sliders);

    void setBGR();
};


#endif //VIDEORECODER_ABSPROC_H
