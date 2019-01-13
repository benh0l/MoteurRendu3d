//
// Created by Benoît on 09/01/2019.
//

#include "model.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>


model::model(std::string filename){
    std::cout << filename << std::endl;
     std::ifstream fichier(filename);
     if(fichier){
         std::string ligne;
         int j = 0;
         while(std::getline(fichier, ligne)){
             if(ligne.size() > 0){
                 j++;
                 //std::cout << "ok ligne : " << j << std::endl;
                 //split each string into 4
                 std::istringstream iss(ligne);
                 std::vector<std::string> results((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
                 //add the 4 new strings into array
                 if(results[0] == "v"){
                     //std::cout << "ok v : " << j << std::endl;
                     verts_.push_back(stof(results[1]));
                     verts_.push_back(stof(results[2]));
                     verts_.push_back(stof(results[3]));
                 }else if(results[0] == "f"){
                     //std::cout << "ok f : " << j << std::endl;
                     for(int i = 1; i < 4; i++){
                         std::string s = results[i];
                         std::string delimiter = "/";
                         std::string token = s.substr(0, s.find(delimiter));
                         faces_.push_back(std::stoi(token));
                     }
                 }
             }

         }
     }
}

model::~model() {

}

int model::nverts() {
    return verts_.size()/3;
}

int model::nfaces() {
    return faces_.size()/3;
}

std::vector<float> model::vert(int i) {
    std::vector<float> res;
    res.push_back(verts_[(i-1)*3]);
    res.push_back(verts_[((i-1)*3)+1]);
    res.push_back(verts_[((i-1)*3)+2]);
    return res;
}

std::vector<int> model::face(int idx) {
    std::vector<int> res;
    res.push_back(faces_[(idx-1)*3]);
    res.push_back(faces_[((idx-1)*3)+1]);
    res.push_back(faces_[((idx-1)*3)+2]);
    return res;
}
