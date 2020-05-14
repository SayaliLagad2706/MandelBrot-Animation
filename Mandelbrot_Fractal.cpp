#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "PPMImage.h"
using namespace std;

void error(const char *err) {
    cerr << err << endl;
    exit(1);
} // error

array2D :: array2D(int xResolution, int yResolution) {
    if(xResolution < 0 || yResolution < 0)
        error("Bad dimensions");

    xRes = xResolution;
    yRes = yResolution;
    xtable = new float*[yRes]; // a ("column") array to hold 'float *' type pointers
    if(xtable == nullptr)
        error("Out of memory");

    // each element of the above array points to a 'row' of xRes elements
    for(int i=0; i < yRes; i++){
        xtable[i] = new float[xRes];
        if(xtable[i] == nullptr)
            error("Out of memory");
    }

    for(int i = 0; i < yRes; i++) {
        for(int j = 0; j < xRes; j++) {
            xtable[i][j] = 45; // store 45 as default pixel data
        }
    }
} // array2D

array2D :: ~array2D() {
    for(int i = 0; i < yRes; i++)
        delete []xtable[i]; // delete each row
    delete []xtable; // delete all columns
} // ~array2D

void array2D :: getSize(int &xResolution, int &yResolution) {
    xResolution = xRes;
    yResolution = yRes;
} // getSize

void array2D :: setValue(int x, int y, float val) {
    if(x < 0 || x >= xRes || y < 0 || y >= yRes)
        error("Out of range");
    xtable[y][x] = val;
} // setValue

float array2D :: getValue(int x, int y) {
    if(x < 0 || x >= xRes || y < 0 || y >= yRes)
        error("Out of range");
    return(xtable[y][x]);
} // getValue

PPMImage :: PPMImage(int xResolution, int yResolution, string imageFileName) : array2D(xResolution, yResolution) {
    filename = imageFileName;
} // PGMImage

void PPMImage :: getResolution(int &xResolution, int &yResolution){
    getSize(xResolution, yResolution);
} // getSize

void PPMImage :: setPixel(int x, int y, float val) {
    setValue(x, y, val);
} // setPixel

float PPMImage :: getPixel(int x, int y) {
    return(getValue(x, y));
} // getPixel

void PPMImage :: writeFile() {
    ofstream fractal(filename);

    // header
    fractal << "P3" << endl; // for PPM image; P2 for PGM image
    fractal << xRes << " " << yRes << endl; // how many columns, how many rows
    fractal << 255 << endl; // largest pixel value we'll be outputting (below)

    // pixel data
    for(int i = 0; i < yRes; i++){
        for(int j = 0; j < xRes; j++){
            float val = getPixel(j, i);
            float t = val/255; // normalize the pixel value

            // RGB value calculation for a smooth color transition
            int r = (int)(9*(1-t)*t*t*t*255);
            int g = (int)(15*(1-t)*(1-t)*t*t*255);
            int b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
            fractal << r << " " << g << " " << b << " ";
        } // next column
    } // next row

    fractal.close();
} // writeFile

ComplexNumber :: ComplexNumber(double i, double j) {
    real = i;
    imag = j;
} // complexNumber

inline ComplexNumber ComplexNumber :: add(ComplexNumber c2) {
    return ComplexNumber(real + c2.real, imag + c2.imag);
} // add

inline ComplexNumber ComplexNumber :: squared() {
    return ComplexNumber(real*real - imag*imag, 2*real*imag);
} // squared

inline double ComplexNumber :: abs() {
    return(sqrt(real*real + imag*imag));
} // abs

inline void ComplexNumber :: prt() {
    cout << real << (imag >= 0 ? "+" : "") << imag << "i "<< endl;
} // prt

int main() {
    int xRes, yRes, iter;
    const int maxIter = 255;
    string filename;
    double Cxmin, Cymin, Cxmax, Cymax;

    ifstream incmd("input.txt");
    if(!incmd) {
        cout<<"Failed to open input commands file!";
        return 0;
    }

    while(!incmd.eof()) {
        incmd >> filename;
        incmd >> Cxmin;
        incmd >> Cymin;
        incmd >> Cxmax;
        incmd >> Cymax;

        PPMImage *p = new PPMImage(320, 320, filename);
        p->getResolution(xRes, yRes);

        const double xRange = Cxmax - Cxmin, yRange = Cymax - Cymin, xScale = xRes - 1.0, yScale = yRes - 1.0;

        p->writeFile(); // create a blank image

        for(int y = 0; y < yRes; y++) {
            for(int x = 0; x < xRes; x++) {
                ComplexNumber c(Cxmin + (x/xScale)*xRange, Cymin + (y/yScale)*yRange);
                ComplexNumber z(0,0);
                iter = 0;

                while((iter <= maxIter) && (z.abs() < 2)) {
                    z = (z.squared()).add(c);
                    iter++;
                }

                if(z.abs() >= 2)
                    p->setPixel(x, y, iter);
                else
                    p->setPixel(x, y, 255);
            }
        }

        p->writeFile();

        delete p;
    }
    incmd.close();
} // main
