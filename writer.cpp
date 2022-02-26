//
// Created by sutclj2 on 10/12/2021.
//

#include "writer.h"

void writer::addImage(std::map<std::string, Mat> pairs) {


    for (const auto &[key, value]: pairs) {
        for (int i = 0; i < pairs.size(); i++) {
            files[key] = value;
        }


    }

}

void writer::writeImages() {

    for (const auto &[key, value]: files) {
        for (int i = 0; i < files.size(); i++) {
            fs::path p=outpath.string()+key+".png";

            imwrite(p.string(),value);

        }


    }

}

void writer::setOutpath(const fs::path &outpath) {
    writer::outpath = outpath;
}
