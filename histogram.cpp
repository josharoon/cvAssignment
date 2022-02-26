//
// Created by sutclj2 on 09/12/2021.
//

#include <iostream>
#include <tuple>
#include "histogram.h"

void histogram::calculateHist(Mat image) {


    //If 1 channel Image we just copy channel 1 into other 3 channels.
    if(image.channels()==1){
        std::vector<cv::Mat> images(3);
        images.at(0)=image;
        images.at(1)=image;
        images.at(2)=image;
        merge(images,image);
    }
/**
 * adapted from code found at https://docs.opencv.org/3.4/d8/dbc/tutorial_histogram_calculation.html
 */
    //calculate histogram
    histImage = Mat( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    split( image, bgr_planes );
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );
}
// normalise pre calculated bgr histogram.
void histogram::normalizeHist() const {
/**
 * adapted from code found at https://docs.opencv.org/3.4/d8/dbc/tutorial_histogram_calculation.html
 */
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
}

//draw rgb histogram visualisation based on pre-calculated histogram  Mats
void histogram::drawHistogram() {
    /**
 * adapted from code found at https://docs.opencv.org/3.4/d8/dbc/tutorial_histogram_calculation.html
 */
    for(int i = 1; i < histSize; i++ )
    {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1)) ),
             Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i)) ),
             Scalar( 255, 0, 0), 2, 8, 0  );

        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1)) ),
             Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i)) ),
             Scalar( 0, 255, 0), 2, 8, 0  );
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1)) ),
             Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i)) ),
             Scalar( 0, 0, 255), 2, 8, 0  );
    }
}

const Mat &histogram::getHistImage() const {

    return histImage;
}

void histogram::setHistImage(const Mat &histImage) {
    histogram::histImage = histImage;
}

void histogram::calculateBgrLookup() {

    for (int i = 0; i < diff_cdfVec.size(); ++i) {
        calcLUT(diff_cdfVec[i], lutVec[i]);
    }

    


}

void histogram::calcLUT(std::vector<std::vector<double>> &diffCDF, Mat &lut) {
    for (int i = 0; i < 256; i++)
    {
        // Find the mapping grayscale of the source gray level I
        // and i's cumulative probability difference
        float min = diffCDF[i][0];
        int index = 0;
        for (int j = 1; j < 256; j++)
        {
            if (min > diffCDF[i][j])
            {
                min = diffCDF[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = static_cast<uchar>(index);
    }
}

const std::vector<Mat*> & histogram::getBgrHist() const {
    return bgrHist;
}

void histogram::calcCdfBGR(std::vector<Mat *> hist2Vec) {
    // Calculate the cumulative probability of the original histogram and the specified histogram
    Mat hist1;
    Mat hist2;
    for (int i = 0; i < hist2Vec.size(); ++i) {
        hist1=*bgrHist[i];
        hist2=*hist2Vec[i];
        calcCDF(hist1, hist2);
        diff_cdfVec.emplace_back(diff_cdf);
    }


}

void histogram::calcCDF(const Mat &hist1, const Mat &hist2) {
    std::vector<double> src_cdf;
    std::vector<double> dst_cdf;
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            src_cdf.emplace_back( hist1.at<float>(i));
            dst_cdf.emplace_back(hist2.at<float>(i));
        }
        else
        {
            src_cdf.emplace_back(src_cdf[i - 1] + hist1.at<float>(i));
            dst_cdf.emplace_back(dst_cdf[i - 1] + hist2.at<float>(i));
        }
    }
    //cdf differences
    for(int i = 0; i < 256; i++)
    for (int j = 0; j < 256; j++)
        diff_cdf[i][j] = fabs(src_cdf[i] - dst_cdf[j]);
}

Mat & histogram::getBgrLut() {
    merge(lutVec,bgrLut);
    return bgrLut;
}

histogram::~histogram() {

}

void histogram::eqHistogramBgr(Mat image) {

    split(image, histImageChan);
    for (int i = 0; i < histImageChan.size(); ++i) {
        equalizeHist(histImageChan[i],histImageChan[i]);
    }
    merge(histImageChan, image);


}

void histogram::matchHistBgr() {


    Mat histSource=b_hist;
    Mat histTarget=r_hist;
    Mat hisTrans=b_hist.clone();
    for (int i = 0; i < histTarget.rows; ++i) {
        bToAmap[cvRound(histTarget.at<float>(i, 0))]=i;

    }

    for (int i = 0; i < histSource.rows; ++i) {

        //get value of a Eq at i
        float a=cvRound(histSource.at<float>(i ,0));
        //get value of b Eq at i
        float b=cvRound(histTarget.at<float>(i,0));
        if (bToAmap[i]){
            aToAmap[(int)b]=bToAmap[i];

        }



        //hisTrans


    }




}

