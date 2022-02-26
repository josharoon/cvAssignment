//
// Created by Josh on 18/01/2022.
//

#include <iostream>
#include <sstream>

#include "results.h"

const std::map<std::string, std::vector<int>> &results::getFiles() const {
    return files;
}

void results::setFiles(const std::map<std::string, std::vector<int>> &files) {
    results::files = files;
}

void results::updateValues(std::string filename, std::vector<int> values) {
    files[filename]=values;
}

void results::printResult(std::string filename) {
    std::vector<int> results =files.find(filename)->second;

    std::cout << std::left << std::setw(15)<< filename<<std::setw(9) << "ZnA Trf" <<std::setw(9) << "ZoneB"<<std::setw(9) << "ZoneC"<<std::setw(9)  << "barrier"<<std::setw(9)  << "Train" << std::endl;

    std::cout << std::left << std::setw(15)  <<"Events  "<< std::setw(9) << results[0]<< std::setw(9) << results[1]<< std::setw(9)  << results[2]<< std::setw(9)  << results[3]<< std::setw(9)  << results[4] << std::endl;
    if(groundTruth.size()>0) {   //we only print this if there is a ground truth to calculate a similarity score.
        std::cout << std::left << std::setw(15) << "Percentage" << std::setw(9) << similarityPercentage[0]
                  << std::setw(9) << similarityPercentage[1] << std::setw(9) << similarityPercentage[2] << std::setw(9)
                  << similarityPercentage[3] << std::setw(9) << similarityPercentage[4] << std::endl;
    }
    std::cout << std::endl;
}


void results::openFile(fs::path path) {
        fileStream.open(path.string() , std::ofstream::out  | std::ofstream::app);
}

void results::closeFile() {
    fileStream.close();
}

void results::writeResult(std::string filename) {
    std::vector<int> results =files.find(filename)->second;
    fileStream << filename<<"," << results[0] <<"," << results[1]   <<"," << results[2]  <<"," << results[3] <<"," << results[4]   << std::endl;

}

void results::writeParams(std::vector<std::vector<int>> params)

{
    for(std::vector<int> p : params){
        for(int i:p ){
            fileStream << i << ",";
        }
    }
    fileStream << "end" << std::endl;
}

void results::loadGroundTruth(fs::path path) {
    inputStream.open(path.string());
    if(inputStream.good()){
        std::string line;
        std::string fileName;
        int val;



        while(std::getline(inputStream, line)) {
            std::stringstream ss(line); // read all lines.
            std::getline(ss, fileName, ',');//get filename
            int i = 0;
            // get all groundTruth values
            while(ss >> val){
                resultsVec[i]=val;
                if(ss.peek() == ',') ss.ignore();
                i++;
            }
            groundTruth[fileName]=resultsVec;

        }
    }
}

bool results::checkSimilar(std::string filename, std::vector<int> values) {

    similarityVec={0,0,0,0,0};
    //Check if the ground truth agrees with our results and record a 1 in the appropriate category where it agrees.
    for(int i=0;i<values.size(); i++){
        if(groundTruth[filename][i] == values[i])similarityVec[i]=1;
    }
    similarity[filename]=similarityVec;
    //We return true if all events agree if they don't we return false so we can record an error.
    if(std::find(similarityVec.begin(), similarityVec.end(), 0) != similarityVec.end())
    {return false;}
    else{return true;}
}

void results::calcSimilarPercentage() {
    int total=similarity.size();
    std::vector<int> matches={0,0,0,0,0};
    for ( const auto &[key, value]: similarity ) {
        for(int i=0;i<matches.size(); i++){
            matches[i]+=value[i];
        }
    }
    for(int i=0;i<matches.size(); i++){
        similarityPercentage[i]=((double)matches[i]/total)*100;
    }
    timePercentage.push_back(similarityPercentage);
}

//detect groundTruth that don't match with ground truth and write file names to report.
void results::writeErrorReport(fs::path path) {
    openFile(std::move(path));
    for ( const auto &[key, value]: similarity ) {
       bool error=false;

       for( int v :value){
           if(v==0)error=true;
       }
        if(error) {
            std::vector<int> results = similarity.find(key)->second;
            fileStream << key << "," << results[0] << "," << results[1] << "," << results[2] << "," << results[3]
                       << "," << results[4] << std::endl;
        }
    }
    fileStream << "Percentage Change over time" << std::endl;
    for(std::vector<double> v: timePercentage){
        fileStream << v[0] << ","<< v[1] << ","<< v[2] << ","<< v[3] << ","<< v[4] << std::endl ;
    }


    closeFile();
}

const std::map<std::string, std::vector<int>> &results::getGroundTruth() const {
    return groundTruth;
}

const std::ofstream &results::getFileStream() const {
    return fileStream;
}







