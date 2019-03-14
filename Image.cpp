#include "Image.h"

void Image::allocateImageMem(){
        image_array = new Pixel*[rows];
        for(int i=0;i<rows;i++){
         //allocate memory for each row
            image_array[i] = new Pixel[cols];
        }
    }
Image::Image(Image *image){
    imageName = image->imageName;
    format= image ->format;
    rows= image->rows;
    cols= image->cols;
    size= image->size;
    allocateImageMem();
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
        setPixel(i,j,image->image_array[i][j].red,image->image_array[i][j].green,image->image_array[i][j].blue);
    }
}
}
void Image::deleteImage(){
    //free 2d image array up
    for(int i=0;i<rows;i++){
        delete [] image_array[i];
    }
    delete [] image_array;

}

void Image::imageRead(){ //read in new image
 ifstream file;
 file.open(imageName);

 if(!file.is_open()){
     cerr<< "Failed to open " << imageName << endl;
     exit(1);
 }
 //read meta info  
 file >> format >>cols >> rows >>size;
 //allocate memory for the image
 allocateImageMem();
 //create image

 for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
        file >> image_array[i][j].red >>image_array[i][j].green>>image_array[i][j].blue;
    }
}
    file.close();

}
int * Image::getPixel(int row, int col){
    int *retArray= new int[3];
    retArray[0]=image_array[row][col].red;
    retArray[1]=image_array[row][col].green;
    retArray[2]=image_array[row][col].blue;
    return retArray;
}
void Image::setPixel(int row,int col,int r,int g,int b){
    image_array[row][col].red=r;
    image_array[row][col].green=g;
    image_array[row][col].blue=b;

}

