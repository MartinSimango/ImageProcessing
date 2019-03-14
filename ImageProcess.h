#pragma once

#include "Image.h"


enum Channel {RED_CHANNEL,GREEN_CHANNEL,BLUE_CHANNEL};
class ImageProcess
{
private:
    /* data */
    Image *image=NULL; 
    void imageRead(string imageName); //read in the image
  
public:

    //contructors
    ImageProcess(string imageName) { image= new Image(imageName);};
    //destructors
    ~ImageProcess(){ }; 
     
    Image* getImage(){return image; };
    
    Image* greyScaleChannel(enum Channel channel); 
    
    void createImageFile(Image* im) const;//create in image file from Image

};
