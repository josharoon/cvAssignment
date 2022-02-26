//
// Created by Josh on 06/01/2022.
//

#include <iostream>
#include "genProc.h"
#include "imageOps.h"


void genProc::procFunc(std::function<Mat &(Mat &, std::vector<int>)> func) {

    output=func(input,sliders);
}

void genProc::procFunc(std::function<Mat &(Mat &, Mat &, std::vector<int>)> func) {

    output=func(inputs[0],inputs[1],sliders);

}

void genProc::setInputs(const std::vector<Mat> &inputs) {
    genProc::inputs = inputs;
}

void genProc::procFunc(std::function<Mat &(Mat &, std::vector<Point2f>)> func) {

    output=func(input,verticies);

}

void genProc::procFunc(std::function<Mat &(Mat &,Scalar, std::vector<Point2f>)> func) {

    output=func(input,color,verticies);

}


void genProc::setVerticies(const std::vector<Point2f> &vertices) {
    genProc::verticies = vertices;
}

void genProc::setColor(const Scalar &color) {
    genProc::color = color;
}

