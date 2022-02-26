//
// Created by Josh on 15/01/2022.
//

#ifndef VIDEORECODER_SEQUENCE_H
#define VIDEORECODER_SEQUENCE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <filesystem>


using namespace cv; // OpenCV API is in the C++ "cv" namespace
namespace fs= std::filesystem;

/**
 * class responsible for managing files as a sequence of images to be analysed
 */
class sequence {
public:
    /**
     * constructor
     * @param seqPath path to folder containing image sequences
     */
    sequence(const fs::path &seqPath);
    /**
     * return next image in sequnece as Mat
     */
    Mat getImage();
    /**
     * returns the filename of the current image in the sequnece
     */
    fs::path getFileName();
    /**
     * allows us to step bacwards through the image sequnece
     */
    Mat prevImage();
    /**
     * returns the number of files in the sequence.
     */
    int getSize();

private:

    fs::path seqPath;
    std::vector<fs::path> filenames;
    int count;
    Mat image;
    void setFilenames();
};


#endif //VIDEORECODER_SEQUENCE_H
