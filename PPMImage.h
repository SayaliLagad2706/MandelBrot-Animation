#ifndef PPMImage_H
#define PPMImage_H
using namespace std;

// class declaration
class array2D {
protected:
    int xRes, yRes;
    float **xtable; // pointer to pointer[s]

public:
	//size of image to be generated
    array2D(int xResolution = 512, int yResolution = 256);
    ~array2D();
    void getSize(int &xResolution, int &yResolution);
    void setValue(int x, int y, float val);
    float getValue(int x, int y);
}; // class array2D

// class declaration
class PPMImage : public array2D {
private:
    string filename;

public:
    PPMImage(int xResolution = 512, int yResolution = 256, string imageFilename = "test.ppm");
    ~PPMImage() {}
    void getResolution(int &xResolution, int &yResolution);
    void setPixel(int x, int y, float val);
    float getPixel(int x, int y);
    void writeFile();
}; // class PPMImage

// class declaration
class ComplexNumber {
private:
    double real, imag;

public:
    ComplexNumber(double i = 0, double j = 0);
    ~ComplexNumber() {}
    ComplexNumber add(ComplexNumber c2);
    ComplexNumber squared();
    double abs();
    void prt();
}; // class complexNumber

#endif // PPMImage_H

