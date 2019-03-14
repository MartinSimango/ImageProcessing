#pragma once 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Pixel {
    int red;
    int blue;
    int green;
};

 class Image{
    private:
     string imageName,format;
     Pixel** image_array; //2d array of the image
     int cols,rows,size;

     //helper functions
    void allocateImageMem(); //allocate memory for the image
    void imageRead(); //read in the image information
    void deleteImage();
    public:

    //constructors
     Image(string imageName):imageName(imageName){ imageRead(); }
   
     Image(string imageName,string format,int row,int col,int size):imageName(imageName),format(format),rows(row),cols(col),size(size){ allocateImageMem();}
    
      //copy contructor
     Image(Image *image);
     //deconstructor
     ~Image(){ deleteImage();}

    //getter methods
     const string getImageName()const{return imageName;}
     const string getImageFormat()const{return format;}
     const int getCols() const {return cols;}
     const int getRows() const {return rows;}
     const int getSize() const {return size;}
     const Pixel** getImageArray() { return (const Pixel**)image_array;};
     
     //setters
     void setImageName(string imageName){this->imageName=imageName;}
     void setImageFormat(string format){this->format=format;}
     void setCols(int cols){this->cols=cols;}
     void setRows(int rows){this->rows=rows;}
     void setPixel(int row,int col,int r,int g,int b);
   
     int* getPixel(int row,int col); //return pixel rgb colors
    
}; 
 