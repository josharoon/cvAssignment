//
// Created by Josh on 15/01/2022.
//

#include "sequence.h"


sequence::sequence(const fs::path &seqPath) : seqPath(seqPath) {

    count=0;
    setFilenames();
}

void sequence::setFilenames() {
    fs::path directory=seqPath.parent_path();
    fs::path extension=seqPath.extension();
    fs::path filename;
    for(auto const& dir_entry: std::filesystem::directory_iterator{directory}){
       filename=dir_entry;
    if(filename.extension() == ".png")filenames.push_back(filename);
    }
}

Mat sequence::getImage() {
    image=imread(filenames[count].string(), IMREAD_COLOR);
    if(count<filenames.size()-1) count ++;
    return image;
}

Mat sequence::prevImage() {
    if(count>0) count --;
    image=imread(filenames[count].string(), IMREAD_COLOR);
    return image;
}

fs::path sequence::getFileName() {
    return filenames[count].filename();
}

int sequence::getSize() {
    return filenames.size();
}

