//
// Created by Josh on 06/01/2022.
//

#include "HoughP.h"
#include "edgeGeo.h"


HoughP::HoughP() {}

void HoughP::detect() {

    HoughLinesP(input, linesP, 1, CV_PI/180, params[4], params[5], params[6] ); // runs the actual detection
}

void HoughP::draw(const Scalar_<int> &color, std::vector<Vec4i> &lineVector) {
    if(input.channels()==1)cvtColor(input,input, COLOR_GRAY2BGR);
    for(size_t i = 0; i < lineVector.size(); i++ )
    {
        Vec4i l = lineVector[i];
        line(input, Point(l[0], l[1]), Point(l[2], l[3]), color, 3, LINE_AA);
    }
    //input.copyTo(output);

}

void HoughP::setParams(const std::vector<int> &params) {
    HoughP::params = params;
}

double HoughP::getAngle(Vec4i line) {
    double y=line[1]-line[3];
    double x=line[2]-line[0];
    return atan2(y,x);
}

double HoughP::length() {
    return Hough::length();
}

void HoughP::validateLines() {

    std::for_each(linesP.begin(),linesP.end(),[this](Vec4i line){

        double angle = this->getAngle(line);
        if(angle > ((double)params[0]*CV_PI/180) && angle < params[1]*CV_PI/180  &&line[1]<params[7] &&line[1]>params[7]-40 &&line[0]<35)
        linesP2.push_back(line);
    });






}

Mat &HoughP::getOutput() {
    linesP.clear();
    linesP2.clear();
    input.copyTo(output);
    return output;
}

int HoughP::getEvents() {
    return linesP2.size();
}
