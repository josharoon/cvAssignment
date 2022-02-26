//
// Created by Josh on 06/01/2022.
//

#include "HoughP.h"
#include "Hough.h"
#include "edgeGeo.h"

void edgeGeo::setInput(const Mat &input) {
    edgeGeo::input = input;
    edgeGeo::output = input;
}

const Mat &edgeGeo::getOutput() const {
    return output;
}