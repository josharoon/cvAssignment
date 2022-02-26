//
// Created by Josh on 06/01/2022.
//

#include <opencv2/core/types.hpp>
#include "absProc.h"

const Mat &absProc::getOutput() const {
    return output;
}

void absProc::setInGrey() {
    if(input.channels()==3)cvtColor( input, input, COLOR_BGR2GRAY );
}

void absProc::setInter1(Mat & in) {
    in.copyTo(this->inter1);
}

const Mat &absProc::getInput() const {
    return input;
}

void absProc::setInput(const Mat &input) {
    absProc::input = input;
}

int absProc::getCount() const {
    return count;
}

void absProc::setCount(int count) {
    absProc::count = count;
}

void absProc::setSliders(const std::vector<int> &sliders) {
    absProc::sliders = sliders;
}

void absProc::setBGR() {

    cvtColor( input, input, COLOR_GRAY2BGR );
}

void absProc::setOutGrey() {
    if(output.channels()==3)cvtColor( output, output, COLOR_BGR2GRAY );
}
