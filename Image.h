#pragma once 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace mycv{
    
    struct Pixel {
        unsigned char rgb[3];
    };
    typedef struct Size{
        int width,height; 
        Size(int width,int height): width(width),height(height){}
    } Size;
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
        const int getWidth() const {return cols;}
        const int getHeight() const {return rows;}
        const int getSize() const {return size;}
        const Pixel** getImageArray() { return (const Pixel**)image_array;};
        
        //setters
        void setImageName(string imageName){this->imageName=imageName;}
        void setImageFormat(string format){this->format=format;}
        void setWidth(int cols){this->cols=cols;}
        void setHeight(int rows){this->rows=rows;}
        void setPixel(int row,int col,unsigned char r,unsigned char g,unsigned char b);
        unsigned char* getPixel(int row,int col); //return pixel rgb colors
        
    }; 
}
 