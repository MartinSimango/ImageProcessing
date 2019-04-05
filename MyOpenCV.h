#pragma once

#include "Image.h"
#include <cmath>
#include <opencv4/opencv2/opencv.hpp>


namespace mycv{
    
    enum Channel {RED_CHANNEL,GREEN_CHANNEL,BLUE_CHANNEL};

    Image * imageRead(string imageName); //read in the image


    //GrayScaling
    Image * grayScaleChannel(Image* image,enum Channel channel); 
    Image * grayScaleAverage(Image *image);
    Image * grayScaleWeightedAverage(Image *image);

    //Scaling 
    Image * scaleNearestNeighbour(Image *image,Size * newSize); //enter scaling factor in %
    Image * scaleInterpolation(Image *image,Size * newSize);

    //Rotation
   
    //rotate about middle of picture
    Image * rotate(Image *image,double angle);

    //rotate about any point
    Image * rotate(Image *image,double angle ,int about_x, int about_y);

    //Background subtraction

    void backgroundSubstraction(int threshold);

    void frameDifference(int threshold);

    void runningAverage(int threshold,float learningRate=0.05);

    //Create an image;
    void createImageFile(Image* im,string filename);//create in image file from Image
 

};
