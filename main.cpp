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

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
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
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
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
    /* std::vector<std::string> tab
    for(int i = 0; i<tab.size(); i+=4){
        std::cout << tab[i] << std::endl;
        if(tab[i] == "v"){
            image.set(std::stof(tab[i+1])*(image.get_height()/2)+(image.get_height()/2) ,std::stof(tab[i+2])*(image.get_width()/2)+(image.get_width()/2), color);
        }else if(tab[i] == "f"){
            std::string s;
            int tabSommet[3];
            for(int j = 1; j < 4; j++){
                s = tab[i+j];
                std::string delimiter = "/";
                std::string token = s.substr(0, s.find(delimiter));
                tabSommet[j-1] = std::stoi(token);
            }
            std::cout << std::stoi(tab[tabSommet[0]*3+1]) << std::endl;
            std::cout << tabSommet[0] << std::endl;
            line(std::stoi(tab[tabSommet[0]*3+1]), std::stoi(tab[tabSommet[0]*3+2]), std::stoi(tab[tabSommet[1]*3+1]), std::stoi(tab[tabSommet[1]*3+2]), image, color);
        }
    }
     */
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
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("../output.tga");
    return 0;
}