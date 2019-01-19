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
const TGAColor green   = TGAColor(0, 255,   0,   255);
const int WIDTH = 1600;
const int HEIGHT = 1600;
const float light[3] = {0.,0.,1.};

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


void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, TGAImage &image, TGAColor color){
        if(y1 > y2) {
            std::swap(y1,y2);
            std::swap(x1,x2);
        }
        if(y1 > y3){
            std::swap(y1,y3);
            std::swap(x1,x3);
        }
        if(y2 > y3){
            std::swap(y2,y3);
            std::swap(x2,x3);
        }
        int height = y3 - y1;
        if(height != 0) {
            for (int i = y1; i <= y2; i++) {
                int segment_height = y2 - y1 + 1;
                float a = (float) (i - y1) / height;
                float b = (float) (i - y1) / segment_height;
                int ax = x1 + (x3 - x1) * a;
                int bx = x1 + (x2 - x1) * b;
                if (ax > bx)
                    std::swap(ax, bx);
                //image.set(ax,i,red);
                //image.set(bx,i,green);
                for (int ii = ax; ii <= bx; ii++) {
                    image.set(ii, i, color);
                }
            }
            for (int j = y2; j <= y3; j++) {
                int segment_height = y3 - y2 + 1;
                float a = (float) (j - y1) / height;
                float b = (float) (j - y2) / segment_height;
                int ax = x1 + (x3 - x1) * a;
                int bx = x2 + (x3 - x2) * b;
                if (ax > bx)
                    std::swap(ax, bx);
                for (int jj = ax; jj <= bx; jj++) {
                    image.set(jj, j, color);
                }
            }
        }
}

void drawVertice(model m, TGAImage &image, TGAColor color){
    std::cout << "nverts : " << m.nverts() << std::endl;
    for(int i = 1; i <= m.nverts(); i++){
        //std::cout << "ok"+i << std::endl;
        std::vector<float> vertice = m.vert(i);
        image.set(vertice[0]*(image.get_width()/2)+(image.get_width()/2), vertice[1]*(image.get_height()/2)+(image.get_height()/2), color);
    }
}

void drawTriangle(model m, TGAImage &image, TGAColor color){
    for(int j = 1; j <= m.nfaces(); j++){
        //std::cout << j << "/" << m.nfaces() << std::endl;
        //WORLD COORDINATES
        std::vector<int> face = m.face(j);
        //SCREEN COORDINATES
        int xA = m.vert(face[0])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yA = m.vert(face[0])[1]*(image.get_height()/2)+(image.get_height()/2);
        int xB = m.vert(face[1])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yB = m.vert(face[1])[1]*(image.get_height()/2)+(image.get_height()/2);
        int xC = m.vert(face[2])[0]*(image.get_width()/2)+(image.get_width()/2);
        int yC = m.vert(face[2])[1]*(image.get_height()/2)+(image.get_height()/2);
        //line(xA,yA,xB,yB,image,color);
        //line(xB,yB,xC,yC,image,color);
        //line(xC,yC,xA,yA,image,color);
        //Take 2 vector from triangle :
        float vector1[3] = {m.vert(face[1])[0] - m.vert(face[0])[0],m.vert(face[1])[1] - m.vert(face[0])[1],m.vert(face[1])[2] - m.vert(face[0])[2]};
        float vector2[3] = {m.vert(face[2])[0] - m.vert(face[1])[0],m.vert(face[2])[1] - m.vert(face[1])[1],m.vert(face[2])[2] - m.vert(face[1])[2]};

        //Do cross-product :
        float normal_surface[3];

        normal_surface[0] = ( vector1[1]*vector2[2] ) - ( vector1[2]*vector2[1] );
        normal_surface[1] = ( vector1[2]*vector2[0] ) - ( vector1[0]*vector2[2] );
        normal_surface[2] = ( vector1[0]*vector2[1] ) - ( vector1[1]*vector2[0] );

        //Calculate norme :
        float norme = sqrtf(normal_surface[0]*normal_surface[0] + normal_surface[1]*normal_surface[1] + normal_surface[2]*normal_surface[2]);
        normal_surface[0] = normal_surface[0] / norme;
        normal_surface[1] = normal_surface[1] / norme;
        normal_surface[2] = normal_surface[2] / norme;


        //Calculate intensity (scalaire) :
        float intensity = normal_surface[0]*light[0] + normal_surface[1]*light[1] + normal_surface[2]*light[2];
        //std::cout << "n z : " << normal_surface[2] << " intensite : " << intensity << std::endl;

        //Draw :
        if(intensity > 0)
            fillTriangle(xA,yA,xB,yB,xC,yC,image,TGAColor(intensity*255, intensity*255, intensity*255, 255));

    }
}

void draw(model m, TGAImage &image, TGAColor color){
    drawVertice(m,image,color);
    drawTriangle(m,image,color);
}

int main(int argc, char** argv) {
    //std::vector<std::string> tab = readFile("../african_head.obj");
    /*
    for(int i =1; i<tab.size(); i++){
        std::cout << tab[i] << std::endl;
    }
    */
    //int light[3] = {0,0,-1};
    model m("../african_head.obj");
    //model m("../diablo_pose.obj");
    TGAImage image(HEIGHT,WIDTH, TGAImage::RGB);
    drawTriangle(m,image, white);
    //fillTriangleTest(10,10,400,100,200,400,image,white);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("../output.tga");
    return 0;
}