// Joshua Sutcliffe Image Processing Assignment 2021 Sn 346658


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <ctime>
#include <filesystem>
#include <string>
#include "histogram.h"
#include "HoughP.h"
#include "contour.h"
#include "genProc.h"
#include "imageOps.h"
#include "sequence.h"
#include "results.h"
#include "writer.h"


using namespace cv;
namespace fs= std::filesystem;


/**
 * runPipe runs the image processing and analysis pipeline
 */
void runPipe(const std::string &windowEventsBoxes, const std::string &windowFG, const std::string &windowDifference,
             const std::string &windowThreshold, const std::string &houghWindow, const std::vector<int> &sliders,
             const std::vector<int> &houghParams, genProc &gP, contour &cont, HoughP &hP, results &r, const Mat &bg,
             std::vector<int> &resultsVec, std::string &CurrentFile, const Mat &fg, String timeString, bool waitkey,
             bool showWindow, bool writeFrames, writer &write);


fs::path indyFile= "C:\\Users\\Josh\\OneDrive - Cranfield University\\ComputerVision\\Assingment\\Individual\\train\\train\\lc-00444.png";
/**
 * We set up vectors of points to describe our Zones
 */
std::vector<Point2f> zoneA ={Point(300,24),Point(460,24),Point(460,300)  ,Point(220,695) ,Point(0,695)   };
std::vector<Point2f> zoneB1 ={Point(180,310),Point(60,114)  ,Point(60,20)  ,Point(300,20)  };
const std::vector<Point2f> zoneB2 ={Point(460,690),Point(200,690),Point(330,500)};
std::vector<Point2f> zoneC1 ={Point(180,310),Point(110,460),Point(55,285),Point(55,115)};
std::vector<Point2f> zoneC2 ={Point(460,300),Point(460,700),Point(340,510)};

/**
 * We set up our command line interface using openCVs command line parser.
 */
const char* keys =
        "{  help|  | Print help message. }"
        "{  root |  | optional project root from which other paths can be set relative to}"
        "{  gt   |  | path to ground truth if using }"
        "{  seq  |  | path to folder containing sequence} "
        "{ frame|  | path to single frame}"
        "{ error|  | path to error report }"
        "{ window| true | show image windows}"
        "{ outFrames|  | path to output folder (if using)}"
        "{ waitkey| false  | if true waits for user to press key before continuing to next frame }"
        "{ results|   | path to results report}"
        "{ bg|   | path to empty images to be averaged}"
        "{ sepImage |   | path to bg image to separate frames against}"
        ;




int main(int argc, char** argv )
{




    /**
      *  Create time string for use in saving groundTruth files.
      */
    time_t rawTime;
    struct tm * timeinfo;
    char buffer [80];
    time(&rawTime);
    timeinfo = localtime (&rawTime);
    String timeString=std::to_string(timeinfo->tm_mday)+std::to_string(timeinfo->tm_hour)+std::to_string(timeinfo->tm_min);



/**
     *  Set user input variables.
     */
    CommandLineParser parser( argc, argv, keys );
    std::cout << "parsing command line inputs" << std::endl << std::endl;
    parser.printErrors();
    fs::path projectRoot="";
    if(!parser.get<String>("root").empty()){
        std::cout << "getting project root" << std::endl;
        projectRoot=parser.get<String>("root");
        std::cout << projectRoot << std::endl;

        if(!fs::exists(projectRoot)) {
            std::cout << "check  projectRoot "<< projectRoot<< " exists";
            return 0;
        }
    }
    bool gt=false;
    fs::path groundTruth;
    if(!parser.get<String>("gt").empty()){
        gt=true;
        groundTruth= projectRoot.string()+parser.get<String>("gt");
        std::cout << "ground truth = " <<groundTruth << std::endl;
        if(!fs::exists(groundTruth)) {
            std::cout << "check ground truth path "<< groundTruth<< " exists";
            return 0;
        }
    }
    bool finalSeq=false;
    fs::path seqPath;
    if(!parser.get<String>("seq").empty()){
        finalSeq=true;
        seqPath= projectRoot.string()+parser.get<String>("seq");
        std::cout << "seqPath = " <<seqPath << std::endl;
        if(!fs::exists(seqPath)) {
            std::cout << "check  seqPath "<< seqPath<< " exists";
            return 0;
        }
    }
    if(!parser.get<String>("frame").empty()){
        indyFile=projectRoot.string()+parser.get<String>("frame");
        if(!fs::exists(indyFile)) {
            std::cout << "check single frame "<< indyFile<< " exists";
            return 0;
        }

    }
    bool errorReport=false;
    fs::path errorRoot;
    if(!parser.get<String>("error").empty()){
        errorReport=true;
        errorRoot= projectRoot.string() + parser.get<String>("error") + "errors_" + timeString + ".csv";
        std::cout << "writing errors to " << errorRoot << std::endl;
    }
    bool showWindow=false;
    if(parser.get<bool>("window"))showWindow=true;
    bool writeFramesBool=false;
    fs::path framePath;
    if(!parser.get<String>("outFrames").empty()){
        writeFramesBool=true;
        framePath=projectRoot.string()+parser.get<String>("outFrames");
        if(!fs::exists(framePath)) {
            std::cout << "check outFrame path "<< framePath<< " exists";
            return 0;
        }
        std::cout << "writing outFrames to " << framePath << std::endl;

    }
    bool waitKeyBool=false;
    if(parser.get<bool>("waitkey"))waitKeyBool=true;
    bool resultReport=false;
    fs::path resultPath;
    if(!parser.get<String>("results").empty()){
        resultReport=true;
        resultPath=projectRoot.string()+parser.get<String>("results") +"results_"+timeString+".csv";
        std::cout << "writing results to " << resultPath << std::endl;
    }


    bool testMode=false;

    /**
     *  create a background for separation by averaging a sequence of frames together if bg path detected
     */
     if (!parser.get<String>("bg").empty()){
         auto path = projectRoot.string() + parser.get<String>("bg");
         sequence bgSeq(path);
         std::cout << "reading background frames from " << path << std::endl;
         Mat avFrame=bgSeq.getImage();
         Mat addFrame;
         avFrame.convertTo(avFrame,CV_32F);
         for (int i = 1; i < bgSeq.getSize()-1; ++i) {
             addFrame=bgSeq.getImage();
             addFrame.convertTo(addFrame,CV_32F);
            add(avFrame,addFrame,avFrame);

         }
           avFrame=avFrame/(float)bgSeq.getSize();
         auto filename = projectRoot.string() + "bgAverage.png";
         imwrite(filename, avFrame);
         std::cout << "written " << filename << std::endl;
         return 0;
     }

/**
 *  If no bg separation image supplied at this stage we need to quit and ask the user to supply one.
 */
    fs::path sepImage;
    if(!parser.get<String>("sepImage").empty()){
        sepImage=projectRoot.string()+parser.get<String>("sepImage");
        std::cout << "sepImage = " <<sepImage << std::endl;
        if(!fs::exists(sepImage)) {
            std::cout << "check  seperation Image "<< sepImage << " exists";
            return 0;
        }
    }



/**
  * Set up windows for displaying images.
 */
    const std::string windowEventsBoxes = "Results_Boxes";
    namedWindow(windowEventsBoxes, 1  );
    const std::string windowFG = "orig FG";
    namedWindow(windowFG, 1);
    const std::string windowThreshold = "Threshold";
    namedWindow(windowThreshold, 1);
    const std::string windowDifference = "Difference";
    namedWindow(windowDifference, 1);
    const std::string houghWindow = "Lines";
    namedWindow(houghWindow, 1);
/**
 * Set up Sliders and Default Values used to control processing and analysis functions
 */

    //Set Default Values
    std::vector<int> sliders={140,61,307,106,338,27,2,2 ,900,3,70};
    std::vector<int> houghParams={15,30,61,307,50,150,27,300};

  /**
   * Hough Window trackbars - uncomment to use for debugging purposes
   */
//    auto track2 = "canny1 \n";
//    createTrackbar(track2, houghWindow, &houghParams[2], 255);
//    setTrackbarPos(track2,houghWindow,1);
//    auto track3 = "canny2 \n";
//    createTrackbar(track3, houghWindow, &houghParams[3], 3000);
//    auto track4= "HougTh";
//    createTrackbar(track4, houghWindow, &houghParams[4], 500);
//    auto track5= "MinLine";
//    createTrackbar(track5, houghWindow, &houghParams[5], 500);
//    auto track6= "Gap";
//    createTrackbar(track6, houghWindow, &houghParams[6], 300);
//    auto minAngleTrack= "Min line Angle";
//    createTrackbar(minAngleTrack, houghWindow, &houghParams[0], 360);
//    auto maxAngleTrack= "Max line Angle";
//    createTrackbar(maxAngleTrack, houghWindow, &houghParams[1], 360);
//    auto yThresh= "Y Line Thresh";
//    createTrackbar(yThresh, houghWindow, &houghParams[7], 480);
    /**
     * Threshold window trackbars - uncomment to use for debugging purposes
     */
//    auto track1 = "Threshold";
//    createTrackbar(track1, windowEventsBoxes, &sliders[0], 255);
//    auto track7= "Shapes";
//    createTrackbar(track7, windowEventsBoxes, &sliders[6], 2);
//    auto track8= "Gblur";
//    createTrackbar(track8, windowEventsBoxes, &sliders[7], 20);
//    auto track9= "Area threshold";
//    createTrackbar(track9, windowEventsBoxes, &sliders[8], 8000);
//    auto track10= "Open";
//    createTrackbar(track10, windowEventsBoxes, &sliders[9], 50);
//    auto track11= "Close";
//    createTrackbar(track11, windowEventsBoxes, &sliders[10], 50);

/**
 * Set up file paths of sequences and files used in project
 */

    //fs::path groundTruth= projectRoot.string() + "ground_truthCSV.csv";

    Mat bg = imread(sepImage.string(), IMREAD_COLOR );

    /**
     * set up sequences for test/dev mode
     */
    std::vector<sequence> sequences;
    if (testMode) {
        fs::path FgPath = (projectRoot.string() + "Individual\\barrier\\barrier\\*.png");
        fs::path FgPath2 = (projectRoot.string() + "Individual\\empty\\empty\\*.png");
        fs::path FgPath3 = (projectRoot.string() + "Individual\\entering\\entering\\*.png");
        fs::path FgPath4 = (projectRoot.string() + "Individual\\leaving\\leaving\\*.png");
        fs::path FgPath5 = (projectRoot.string() + "Individual\\ontrack\\ontrack\\*.png");
        fs::path FgPath6 = (projectRoot.string() + "Individual\\train\\train\\*.png");
        sequence seq(FgPath);
        sequence seq2(FgPath2);
        sequence seq3(FgPath3);
        sequence seq4(FgPath4);
        sequence seq5(FgPath5);
        sequence seq6(FgPath6);
        //std::vector<sequence> sequences{seq2};
        //std::vector<sequence> sequences{seq4};
        //std::vector<sequence> sequences{seq6};
        sequences={seq,seq2,seq3,seq4,seq5,seq6};
    }else if(finalSeq){

        if (fs::exists(seqPath)) {
            sequence seq(seqPath);
            sequences = {seq};
        } else {
            std::cout << "Please check sequence " << seqPath << "exists" << std::endl;
            return 0;
        }
    }
    /**
     * set up sequence for user mode.
     */


/**
 * Instantiate all objects used in processing images and storing data
 */

    genProc gP;

    contour cont;
    HoughP hP;
    results r;
    writer w;
    std::vector<KeyPoint> keypoints;
    std::vector<int> resultsVec;
    Mat fg;
    w.setOutpath(framePath);

    // if working as a sequence.
/**
 * Set up Image sequences for analysis
 */
    if(testMode || finalSeq){
        r.openFile(resultPath.string());
        int count=0;
        r.writeParams({houghParams,sliders});
        r.loadGroundTruth(groundTruth);
        for(sequence s : sequences){
            count++;
            for(int i = 0;i< s.getSize();i++) {
                resultsVec = {0, 0, 0, 0, 0};
                std::string CurrentFile = s.getFileName().string();
                r.setFiles({{CurrentFile, resultsVec}});
                fg = s.getImage();
                //loop through sequences then frames and run image pipeline.
                runPipe(windowEventsBoxes, windowFG, windowThreshold, windowDifference, houghWindow, sliders,
                        houghParams,
                        gP, cont, hP,
                        r, bg,
                        resultsVec, CurrentFile, fg, timeString, waitKeyBool, showWindow, writeFramesBool, w);
            }

        }

        r.closeFile();
        r.writeErrorReport(errorRoot);
/**
 *  else set up for single frame mode.
 */
    }else{

        resultsVec = {0, 0, 0, 0, 0};
        std::string CurrentFile = indyFile.filename().string();
        r.setFiles({{CurrentFile, resultsVec}});
        fg=imread(indyFile.string(),IMREAD_COLOR);
        while(waitKey(1) != 27)
        {
            //run the pipeline on a single frame.
            runPipe(windowEventsBoxes, windowFG, windowThreshold, windowDifference, houghWindow, sliders, houghParams,
                    gP, cont, hP,
                    r, bg,
                    resultsVec, CurrentFile, fg, timeString, waitKeyBool, showWindow, writeFramesBool, w);
        }
    }







    return 0;


}

void runPipe(const std::string &windowEventsBoxes, const std::string &windowFG, const std::string &windowDifference,
             const std::string &windowThreshold, const std::string &houghWindow, const std::vector<int> &sliders,
             const std::vector<int> &houghParams, genProc &gP, contour &cont, HoughP &hP, results &r, const Mat &bg,
             std::vector<int> &resultsVec, std::string &CurrentFile, const Mat &fg, String timeString, bool waitkey,
             bool showWindow, bool writeFrames, writer &write) {
    Mat  fg1,fg2,bg1,diff,zb1,zb2,zc1,zc2,zB,zC,zA,thresh1,thresh2,hLines, FinalComp,hist1,hist2 , diffOut,zoneIm ;
    fs::path filename=CurrentFile;
    std::map<std::string,Mat> imagePairs;
//    fs::path errorRoot=("C:\\Users\\Josh\\OneDrive - Cranfield University\\ComputerVision\\Assingment\\ErrorFrames\\");


    /**
     * Start Pre Processing
     */
    histogram fgH,bgH,diffHist;
    fgH.setHistImage(hist1);
    fgH.eqHistogramBgr(fg);
    bgH.setHistImage(hist2);
    bgH.eqHistogramBgr(bg);
    fgH.calculateHist(fg);
    fgH.normalizeHist();
    bgH.calculateHist(bg);
    bgH.normalizeHist();


    genProc zoneMap;
    if (showWindow) {
    fgH.drawHistogram();
    bgH.drawHistogram();
    hist1=fgH.getHistImage();
        const std::string windowFGHist = "FGHist";
        namedWindow(windowFGHist, 1);
        imshow(windowFGHist, hist1);
        hist2 = bgH.getHistImage();
        const std::string windowBGHist = "BGHist";
        namedWindow(windowBGHist, 1);
        imshow(windowBGHist, hist2);

        zoneMap.setInput(fg.clone());
        zoneMap.setColor(Scalar_(200, 200, 255));
        zoneMap.setVerticies(zoneA);
        zoneMap.procFunc(imageOps::colorZone);
        zoneMap.setColor(Scalar_(255, 200, 200));
        zoneMap.setVerticies(zoneB1);
        zoneMap.procFunc(imageOps::colorZone);
        zoneMap.setVerticies(zoneB2);
        zoneMap.procFunc(imageOps::colorZone);
        zoneMap.setColor(Scalar_(200, 255, 200));
        zoneMap.setVerticies(zoneC1);
        zoneMap.procFunc(imageOps::colorZone);
        zoneMap.setVerticies(zoneC2);
        zoneMap.procFunc(imageOps::colorZone);
    }


    fg1=fg.clone();
    bg1=bg.clone();


    gP.setSliders(sliders);
    gP.setInput(fg1);
    //gP.setInGrey();
    gP.procFunc(imageOps::GausBlur);
    fg1 = gP.getOutput();
    //equalizeHist(fg1,fg1);
    hLines=fg1.clone();
    gP.setInput(bg1);


    gP.procFunc(imageOps::GausBlur);
    bg1= gP.getOutput();
    //equalizeHist(bg1,bg1);
    gP.setInputs(std::vector<Mat>{fg1,bg1});
    gP.procFunc(imageOps::absDiff);
    gP.setOutGrey();
    fg1=gP.getOutput();
    //equalizeHist(fg1,fg1);

    if(showWindow)imshow(windowThreshold, fg1);
    imagePairs[filename.stem().string()+"Difference_"+timeString]=fg1.clone();


    //Thresholding
    gP.setInput(fg1);
    gP.procFunc(imageOps::Open);
    gP.procFunc(imageOps::Close);
    gP.procFunc(imageOps::basicThreshold);
    zb1 = gP.getOutput();
    zb2=fg1.clone();
    zc1=fg1.clone();
    zc2=fg1.clone();
    zA=fg1.clone();
    if(showWindow)imshow(windowDifference, fg1);
    imagePairs[filename.stem().string()+"Threshold_"+timeString]=fg1;
    /**
     *  zone B (a road vehicle is leaving the railway line crossing)
     */
    gP.setVerticies(zoneB1);
    gP.setInput(zb1);
    gP.setInGrey();
    gP.procFunc(imageOps::setZone);

    zb1 = gP.getOutput();
    gP.setVerticies(zoneB2);
    gP.setInput(zb2);
    gP.setInGrey();
    gP.procFunc(imageOps::setZone);

    zb2 = gP.getOutput();
    add(zb1,zb2,zB);
    cont.setInput(zB);
    cont.detect();
    cont.setAreaThreshold(sliders[8]);
    cont.draw();
    cont.aproximateContours();
    cont.detectVehicleEvent();
    /**
     * Record Zone B event
     */
    if(cont.getVehicleEvents() > 0)resultsVec[1]=1;
    zB=cont.getOutput();
    /**
     * Zone C (a road vehicle is leaving the railway line crossing)
     */
    gP.setVerticies(zoneC1);
    gP.setInput(zc1);
    gP.setInGrey();
    gP.procFunc(imageOps::setZone);
    zc1 = gP.getOutput();
    gP.setVerticies(zoneC2);
    gP.setInput(zc2);
    gP.setInGrey();
    gP.procFunc(imageOps::setZone);
    zc2 = gP.getOutput();
    add(zc1,zc2,zC);
    cont.setInput(zC);
    cont.detect();
    cont.setAreaThreshold(sliders[8]);
    cont.draw();
    cont.aproximateContours();
    cont.detectVehicleEvent();
    /**
     * Record Zone C event
     */
    if(cont.getVehicleEvents() > 0)resultsVec[2]=1;
    zC=cont.getOutput();
    /**
     * Zone A (detect train events and vehicle events)
     */
    gP.setVerticies(zoneA);
    gP.setInput(zA);
    gP.setInGrey();
    gP.procFunc(imageOps::setZone);
    zA = gP.getOutput();
    cont.setInput(zA);
    cont.detect();
    cont.setAreaThreshold(sliders[8]);
    cont.setTrainAreaThreshold(sliders[8]*6); // at the moment a train must be at least 6* min car area;
    cont.setAngleTolerance(50.0,90);  //to be fine tuned later.
    cont.draw();
    cont.aproximateContours();
    cont.detectVehicleEvent();
    cont.detectTrainEvent();
    /**
     *  Record Vechicle/Road Traffic Event
     */
    //we don't record a vehicle event in zone A if we detect a train.
    if(cont.getVehicleEvents() > 0 && cont.getTrainEvents() == 0)resultsVec[0]=1;
    /**
     * Record Train Event
     */
    if(cont.getTrainEvents() > 0)resultsVec[4]=1;
    zA=cont.getOutput();
    /**
     * The Barrier is Deployed
     */
    gP.setInput(hLines);
    gP.setSliders(houghParams);
    gP.setInGrey();
    gP.procFunc(imageOps::canny);
    hLines=gP.getOutput();
    hP.setParams(houghParams);
    hP.setInput(hLines);
    hP.detect();
    hP.validateLines();
    hP.draw(Scalar(0, 0, 255), hP.linesP);
    hP.draw(Scalar(0, 255, 0), hP.linesP2);
    /**
     * Record Barrier Event
     */
    if(hP.getEvents()>0)resultsVec[3]=1;
     if(showWindow)imshow(houghWindow, hP.getOutput());
    imagePairs[filename.stem().string()+"HoughLines_"+timeString]= hP.getOutput();
 /**
  * Display Results
  */
    add(zB,zC,FinalComp);
    add(zA,FinalComp,FinalComp);
     if(showWindow)imshow(windowEventsBoxes, FinalComp);
    imagePairs[filename.stem().string()+"EventBoxes_"+timeString]=FinalComp;

    if(showWindow)imshow(windowFG, zoneMap.getOutput());


/**
 *  Set and Evaluate Results
 */
    r.updateValues(CurrentFile,resultsVec);
    if(r.getGroundTruth().size()>0)r.checkSimilar(CurrentFile,resultsVec);
    if(showWindow)imagePairs[filename.stem().string()+"Orig_"+timeString]=zoneMap.getOutput();
    //uncomment this line if we want just error frames written out
    //if(!r.checkSimilar(CurrentFile,resultsVec)==false)write.addImage(imagePairs);
    write.addImage(imagePairs);
    if(r.getGroundTruth().size()>0)r.calcSimilarPercentage();
    r.printResult(CurrentFile);
 /**
 *  Write Out Images
 */
 if(r.getFileStream().is_open())r.writeResult(CurrentFile);
    if(writeFrames)write.writeImages();

    int wait = 1;
    if(waitkey)wait=0;
    char ch = (char) waitKey(wait);


}





