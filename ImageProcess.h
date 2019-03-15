#pragma once

#include "Image.h"


enum Channel {RED_CHANNEL,GREEN_CHANNEL,BLUE_CHANNEL};
class ImageProcess
{
private:
    /* data */
    Image *image; 
    void imageRead(string imageName); //read in the image
  
public:

    //contructors
    ImageProcess(string imageName) { image= new Image(imageName);};
    //destructors
    ~ImageProcess(){ }; 
     
    Image* getImage(){return image; };
    

    //GrayScaling
    Image* grayScaleChannel(enum Channel channel); 
    Image * grayScaleAverage();
    Image * grayScaleWeightedAverage();

    //Scaling 
    Image * scaleNearestNeighbour(int scaleFactor); //enter scaling factor in %
    
    void createImageFile(Image* im,string filename) const;//create in image file from Image

};
