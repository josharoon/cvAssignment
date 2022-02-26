
#ifndef VIDEORECODER_HISTOGRAM_H
#define VIDEORECODER_HISTOGRAM_H


#include <vector>
#include <opencv2/core.hpp>
#include <tuple>
#include <opencv2/imgproc.hpp>
#include <map>

using namespace cv;

/**
 * A class for building,displaying,and manipulating histograms
 */
class histogram {
public:
    histogram(){
        range[0]=0;
        range[1]=256;
        histRange[0]=&range[0];
        histRange[1]=&range[1];
        bin_w = cvRound( (double) hist_w/histSize );
        histImage = Mat( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    }


    void setHistImage(const Mat &histImage);

    const Mat &getHistImage() const;


    void calculateHist(Mat image);

    void drawHistogram();

    void normalizeHist() const;

    virtual ~histogram();

private:
    int histSize = 256;
    std::vector<Mat> bgr_planes;
    int hist_w = 512, hist_h = 400;
    Mat histImage;
    std::vector<Mat> histImageChan;
    int bin_w;
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    std::vector<Mat*> bgrHist{&b_hist,&g_hist,&r_hist};
    std::vector<std::vector<double>> diff_cdf =std::vector<std::vector<double>>(256.0 , std::vector<double> (256));
    //for multiple channels we store our diffCDF vectors in channels.
    std::vector<std::vector<std::vector<double>>> diff_cdfVec;
    float range[2] ;
    const float* histRange[2];
    std::vector<std::tuple<int,int>> blut;
    std::vector<std::tuple<int,int>> glut;
    std::vector<std::tuple<int,int>> rlut;
    std::map<int, int> bToAmap;
    std::map<int, int> aToAmap;


    void calcCDF(const Mat &hist1, const Mat &hist2);

    void calcLUT(std::vector<std::vector<double>> &diffCDF, Mat &lut);


public:
    const std::vector<Mat*> &getBgrHist() const;
    void calculateBgrLookup();

    void calcCdfBGR(std::vector<Mat *> hist2Vec);
    Mat Blut=Mat(1, 256, CV_8U);
    Mat Glut=Mat(1, 256, CV_8U);
    Mat Rlut=Mat(1, 256, CV_8U);
    Mat bgrLut=Mat(1, 256, CV_8U);
    Mat tempLut=Mat(1, 256, CV_8U);

    std::vector<Mat> lutVec={Blut,Glut,Rlut};

    void eqHistogramBgr(Mat image);
    void matchHistBgr();



    Mat & getBgrLut();
};


#endif //VIDEORECODER_HISTOGRAM_H
