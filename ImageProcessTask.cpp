#include "ImageProcess.h"


int main(int argc, char *argv[]){
     
	 //GrayScale 
	ImageProcess image(argv[1]);
	//single channel
	Image* greyC=image.grayScaleChannel((Channel)atoi(argv[2]));
	image.createImageFile(greyC,greyC->getImageName());
	// average grayScale
	greyC= image.grayScaleAverage();
	image.createImageFile(greyC,greyC->getImageName());
	//weighted average
	greyC= image.grayScaleWeightedAverage();
	image.createImageFile(greyC,greyC->getImageName());


	//Scaling
	


}
