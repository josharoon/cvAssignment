//
// Created by Josh on 12/01/2022.
//

#include "genProc.h"
#include <iostream>
#include "imageOps.h"


[[maybe_unused]] Mat & imageOps::multiplyColor(Mat &inMat, std::vector<int> params) {
    inMat=inMat*2;
    return inMat;
}

Mat &imageOps::DivideColor(Mat &inMat, std::vector<int> params) {
    inMat=inMat/params[0];
    return inMat;
}

Mat &imageOps::GausBlur(Mat &inMat, std::vector<int> params) {
    if(params[7]%2 == 0 ||params[7]==0)params[7]++;
    GaussianBlur(inMat,inMat,Size(params[7],params[7]),0,0);
    return inMat;
}

Mat &imageOps::Open(Mat &inMat, std::vector<int> params) {
    if(params[9]==0)params[9]++;
    Mat element = getStructuringElement(params[6],Size(params[9],params[9]));
    morphologyEx(inMat, inMat, MORPH_OPEN ,element);
    return inMat;
}

Mat &imageOps::Close(Mat &inMat, std::vector<int> params) {
    if(params[10]==0)params[10]++;
    Mat element = getStructuringElement(params[6],Size(params[10],params[10]));
    morphologyEx(inMat, inMat, MORPH_CLOSE ,element);
    return inMat;
}
Mat &imageOps::canny(Mat &inMat, std::vector<int> params) {
    Canny(inMat, inMat, params[2], params[3]);
    return inMat;
}


Mat &imageOps::absDiff(Mat &inMat, Mat &inMat2, std::vector<int> params) {
    absdiff(inMat,inMat2,inMat);
    return inMat;
}

Mat &imageOps::adapThreshold(Mat &inMat, std::vector<int> params) {
    int blockSize=params[2];
    if(blockSize%2==0)blockSize++;
    if(blockSize<5)blockSize=5;
    adaptiveThreshold(inMat, inMat,params[0],params[1],THRESH_BINARY,blockSize,params[3]*-1);
    return inMat;
}

Mat &imageOps::setZone(Mat &inMat, std::vector<Point2f> params) {

    inMat.forEach<uint8_t>([&](uint8_t &pixel, const int position[]) -> void {
        if(pointPolygonTest(params,Point(position[0],position[1]),false)==-1)pixel=0;
    });
    return inMat;
}

Mat &imageOps::colorZone(Mat &inMat,Scalar color, std::vector<Point2f> params) {
typedef cv::Point3_<uint8_t> Pixel;
inMat.forEach<Pixel>([&](Pixel &pixel, const int position[]) -> void {
if(
pointPolygonTest(params, Point(position[0], position[1]),
false)==1){
pixel.
y = pixel.y * (color[0] / 255);
pixel.
x = pixel.x * (color[1] / 255);
pixel.
z = pixel.z * (color[2] / 255);
}
});
return inMat;
}


Mat &imageOps::basicThreshold(Mat &inMat, std::vector<int> params) {
    threshold(inMat,inMat,params[0],255,THRESH_BINARY);
    return inMat;
}
