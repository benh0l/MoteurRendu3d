//
// Created by Benoît on 09/01/2019.
//

#ifndef MOTEURRENDU3D_MODEL_H
#define MOTEURRENDU3D_MODEL_H


#include <vector>
#include <fstream>

class model {

private:
    std::vector<float> verts_;
    std::vector<int> faces_;
public:
    model(std::string filename);
    ~model();
    int nverts();
    int nfaces();
    std::vector<float> vert(int i);
    std::vector<int> face(int idx);

};


#endif //MOTEURRENDU3D_MODEL_H

