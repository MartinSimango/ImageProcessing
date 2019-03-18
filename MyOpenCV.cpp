#include "MyOpenCV.h"

 
namespace mycv{


    Image * imageRead(string imageName){
    
    return new Image(imageName);

    }
    Image* grayScaleChannel(Image *image,enum Channel channel){
    
    string colors[]= {"RED","GREEN","BLUE"};

    string greyImageName= colors[channel] + image->getImageName();
    Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());

    for(int i=0;i<image->getHeight();i++){ 
            for(int j=0;j<image->getWidth();j++){
            unsigned char * rgb =image->getPixel(i,j);
            unsigned char grayC= rgb[channel];
            
            retImage->setPixel(i,j,grayC,grayC,grayC);
            delete  [] rgb;
        }
        
    }
    
        return retImage;
    }

    Image * grayScaleAverage(Image *image){
        string greyImageName= "averageGrey" +image->getImageName();
        Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());
        for(int i=0;i<image->getHeight();i++){  
            for(int j=0;j<image->getWidth();j++){
        
                unsigned char * rgb =image->getPixel(i,j);
                unsigned char average = (unsigned char) (((int)rgb[0]+(int)rgb[1]+(int)rgb[2])/3);
                retImage->setPixel(i,j,average,average,average);
                delete  [] rgb;
        }
        
    }
    
        return retImage;


    }

    Image * grayScaleWeightedAverage(Image *image){
        string greyImageName= "weightedGrey" +image->getImageName();
        Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());
        for(int i=0;i<image->getHeight();i++){ 
            for(int j=0;j<image->getWidth();j++){
                unsigned char * rgb =image->getPixel(i,j);
                int gray= 0.3*(int)rgb[0]+0.59*(int)rgb[1]+0.11*(int)rgb[2];
                retImage->setPixel(i,j,gray,gray,gray);
                delete  [] rgb;
        }
        
    }
    
        return retImage;


    }
    Image * scaleNearestNeighbour(Image *image,Size * newSize){ //enter  new size
        string newImageName = "ResizeNearest"+image->getImageName(); 
        Image *retImage = new Image(newImageName,image->getImageFormat(),newSize->height,newSize->width,image->getSize());
 
        int x_ratio = (int)((image->getWidth()<<16)/newSize->width) +1;
        int y_ratio = (int)((image->getHeight()<<16)/newSize->height) +1;
    
        int x2, y2 ;
    
        for(int i=0;i<retImage->getHeight();i++){
            for(int j=0;j<retImage->getWidth();j++){
                 x2 = ((j*x_ratio)>>16);
                 y2 = ((i*y_ratio)>>16);
                
                 unsigned char * rgb = image->getPixel(y2,x2);
                 retImage->setPixel(i,j,rgb[0],rgb[1],rgb[2]);
                delete [] rgb; //free memoery
                //insert code here
            }
        }

        return retImage;


    }
    Image * scaleInterpolation(Image *image,Size * newSize){ //enter  new size
        string newImageName = "ResizeInterpolation"+image->getImageName(); 
        Image *retImage = new Image(newImageName,image->getImageFormat(),newSize->height,newSize->width,image->getSize());
        for(int i=0;i<retImage->getHeight();i++){
            for(int j=0;j<retImage->getWidth();j++){

                //insert code here
            }
        }

        return retImage;


    }


    void createImageFile(Image* im,string filename) {//create in image file from Image
        ofstream file;
        file.open(filename,ios::binary|ios::out);
        if(!file.is_open()){
            cerr<< "Failed to open " << im->getImageName()<< endl;
            exit(1);
    }


        file << im->getImageFormat() <<endl <<im->getWidth() <<" " <<im->getHeight() <<"\n" <<im->getSize() << endl;

        for(int i=0;i<im->getHeight();i++){
            for(int j=0;j<im->getWidth();j++){
                unsigned char * rgb =im->getPixel(i,j); 
                file << rgb[0]<<rgb[1]<<rgb[2];

        
            }
        }

    }

}
