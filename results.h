//
// Created by Josh on 18/01/2022.
//

#ifndef VIDEORECODER_RESULTS_H
#define VIDEORECODER_RESULTS_H


#include <filesystem>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

namespace fs= std::filesystem;

/**
 * responsible, for storing groundTruth,exporting groundTruth, printing groundTruth and comapring them to a ground truth
 */
class results {


private:
    std::vector<int> resultsVec={0,0,0,0,0};
    std::vector<int> similarityVec={0,0,0,0,0};
    std::vector<double> similarityPercentage={0,0,0,0,0};
    std::vector<std::vector<double>>timePercentage;
    std::map<std::string,std::vector<int>> files;
    std::map<std::string,std::vector<int>> groundTruth;
    std::map<std::string,std::vector<int>> similarity;
    std::ofstream fileStream;
    std:: ifstream inputStream;
    time_t time;
public:
    const std::ofstream &getFileStream() const;

public:/**
 * returns dictionary of files mapped to groundTruth
 */
    const std::map<std::string, std::vector<int>> &getGroundTruth() const;

    const std::map<std::string, std::vector<int>> &getFiles() const;
    /**
     * loads a ground truth csv to perform running comparison with groundTruth
     * @param path path to csv
     */
    void loadGroundTruth(fs::path path);
    /**
    *  sets the Files map up
    *  @param files map of filenames and groundTruth
    */
    void setFiles(const std::map<std::string, std::vector<int>> &files);
    /**
     * adds an individual entry to the files map
     * @param filename  filename to be added
     * @param values result values to be associated with the filename.
     */
    void updateValues(std::string filename, std::vector<int> values);
    /**
     *  performs a comparison between detected events and the ground truth in a new vector
      * @param filename  filename
     * @param values result values to be compared with the ground truth.
     */
    bool checkSimilar(std::string filename, std::vector<int> values);
    /**
     * calculates a running percentage acuracy of correct classifaction of events on all files
     * analysed so far
     */
    void calcSimilarPercentage();
    /**
     * prints groundTruth to console
     * @param filename filename of groundTruth to print
     */
    void printResult(std::string filename);
    /**
     * open filestream  for output and appending.
     * @param path path of file to be opened
     */
    void openFile(fs::path path);
    /**
     * close filestream
     */
    void closeFile();
    /**
     * write groundTruth out in csv format
     * @param filename filename to write groundTruth out
     */
    void writeResult(std::string filename);
    /**
     * write params used to groundTruth file so they can be used for later comparison.
     * @param params of parameters used
     */
    void writeParams(std::vector<std::vector<int>> params);
    /**
     * writes an error report of the whole sequence to specified file path
     * @param path path to write error report to.
     */
    void writeErrorReport(fs::path path);



};


#endif //VIDEORECODER_RESULTS_H
