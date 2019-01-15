#include "tgaimage.h"
#include "model.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <sstream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

std::vector<std::vector<int>> line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    std::vector<int> tabX, tabY;
    std::vector<std::vector<int>> res;
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
            tabX.push_back(y);
            tabY.push_back(x);
        } else {
            image.set(x, y, color);
            tabX.push_back(x);
            tabY.push_back(y);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }

    }
    res.push_back(tabX);
    res.push_back(tabY);
    return res;
}

std::vector<std::string> readFile(std::string file){
    std::ifstream fichier(file);
    std::vector<std::string> line;
    if(fichier){
        std::string ligne;
        while(std::getline(fichier, ligne)){
            //split each string into 4
            std::istringstream iss(ligne);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
            //add the 4 new strings into array
            for(int i = 0 ; i<results.size(); i++){
                line.push_back(results[i]);
            }
        }
    }
    return line;
}

void draw(model m, TGAImage &image, TGAColor color){
    std::cout << "nverts : "+m.nverts() << std::endl;
    for(int i = 1; i <= m.nverts(); i++){
        //std::cout << "ok"+i << std::endl;
        std::vector<float> vertice = m.vert(i);
        image.set(vertice[0]*(image.get_width()/2)+(image.get_width()/2), vertice[1]*(image.get_height()/2)+(image.get_height()/2), color);
    }
    for(int j = 1; j <= m.nfaces(); j++){
        std::vector<int> face = m.face(j);
        int xA = m.vert(face[0])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yA = m.vert(face[0])[1]*(image.get_height()/2)+(image.get_height()/2);
        int xB = m.vert(face[1])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yB = m.vert(face[1])[1]*(image.get_height()/2)+(image.get_height()/2);
        int xC = m.vert(face[2])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yC = m.vert(face[2])[1]*(image.get_height()/2)+(image.get_height()/2);
        line(xA,yA,xB,yB,image,color);
        line(xB,yB,xC,yC,image,color);
        line(xC,yC,xA,yA,image,color);
    }
}

void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, TGAImage &image, TGAColor color){
    std::vector<std::vector<int>> res1, res2, res3;
    res1 = line(x1,y1,x2,y2, image, color);
    res2 = line(x2,y2,x3,y3, image, color);
    res3 = line(x3,y3,x1,y1, image, color);
    for(int i = 0; i < res1[0].size(); i++)
        line(x3,y3,res1[0][i],res1[1][i],image,color);
    for(int i = 0; i < res2[0].size(); i++)
        line(x1,y1,res2[0][i],res2[1][i],image,color);
    for(int i = 0; i < res3[0].size(); i++)
        line(x2,y2,res3[0][i],res3[1][i],image,color);
}

int main(int argc, char** argv) {
    //std::vector<std::string> tab = readFile("../african_head.obj");
    /*
    for(int i =1; i<tab.size(); i++){
        std::cout << tab[i] << std::endl;
    }
    */
    model m("../african_head.obj");
    TGAImage image(500,500, TGAImage::RGB);
    draw(m,image, white);
    //fillTriangle(10,10,400,100,200,400,image,red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("../output.tga");
    return 0;
}