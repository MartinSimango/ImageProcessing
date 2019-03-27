#include "Image.h"

namespace mycv
{
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
            setPixel(i,j,image->image_array[i][j].rgb[0],image->image_array[i][j].rgb[1],image->image_array[i][j].rgb[2]);
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
    file.open(imageName,ios::binary | ios::in);

    if(!file.is_open()){
        cerr<< "Failed to open " << imageName << endl;
        exit(1);
    }
    //read meta info  
    file >> format >>cols >> rows >>size;
    //allocate memory for the image
    allocateImageMem();
    //create image
    string input;
    int max=rows*cols*3;
    int count=0;
    int current_row=0;
    int current_col=0;
    int current_color=0;
    
    unsigned char c;
    file>>noskipws;
    file >>c; //skip \n after size
    while(count<max){
        
        file>>c;
        //cout <<c;
        image_array[current_row][current_col].rgb[current_color]=c;
        //cout << image_array[current_row][current_col].rgb[current_color];
        if(current_color==2)current_col++;
        if(current_col==cols){
            current_col=0;
            current_row++;
        }
        current_color=(current_color+ 1) %3;
        count++;

    }
    
        file.close();

    }

    unsigned char * Image::getPixel(int row, int col){
        unsigned char *retArray= new unsigned char[3];
        retArray[0]=image_array[row][col].rgb[0];
        retArray[1]=image_array[row][col].rgb[1];
        retArray[2]=image_array[row][col].rgb[2];
        return retArray;
    }
    void Image::setPixel(int row,int col,unsigned char r,unsigned char g, unsigned char b){
        image_array[row][col].rgb[0]=r;
        image_array[row][col].rgb[1]=g;
        image_array[row][col].rgb[2]=b;

    } 
}
