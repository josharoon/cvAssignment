//
// Created by sutclj2 on 10/12/2021.
//

#ifndef VIDEORECODER_WRITER_H
#define VIDEORECODER_WRITER_H


#include <string>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <map>

namespace fs= std::filesystem;
using namespace cv;
/**
 * class to handle writing of images that are used in the report and for debugging
 */

class writer {

    private:

        std::map<std::string,Mat> files;
        fs::path outpath;
        std::string outfile = outpath.string();


    public:
    /**
     * set path of where to write out put image
     * @param outpath file path of where to put images
     */
        void setOutpath(const fs::path &outpath);
        /**
         * add an image and filename to the list of images to be written
         * @param pairs  a map entry of a filemame and corresponding image matrix
         */
        void addImage(std::map<std::string, Mat> pairs);
        /**
         * write out our collection images in one pass.
         */
        void writeImages();



};


#endif //VIDEORECODER_WRITER_H
