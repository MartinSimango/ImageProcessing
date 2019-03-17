#pragma once

#include "Image.h"




namespace mycv{
    
    enum Channel {RED_CHANNEL,GREEN_CHANNEL,BLUE_CHANNEL};

    Image * imageRead(string imageName); //read in the image


    //GrayScaling
    Image* grayScaleChannel(Image* image,enum Channel channel); 
    Image * grayScaleAverage(Image *image);
    Image * grayScaleWeightedAverage(Image *image);

    //Scaling 
    Image * scaleNearestNeighbour(Image *image,int scaleFactor); //enter scaling factor in %
    
    void createImageFile(Image* im,string filename);//create in image file from Image

};
