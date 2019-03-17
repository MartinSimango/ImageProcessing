#include "ImageProcess.h"


using namespace mycv;

int main(int argc, char *argv[]){
     
	 //GrayScale 
	Image *image =  imageRead(argv[1]);
	Image *grayC;
	//single channel
	grayC = grayScaleChannel(image,(Channel)(atoi(argv[2])));
	cout << "Creating " << grayC->getImageName() <<endl;
	createImageFile(grayC,grayC->getImageName());
	
    // average grayScale
	grayC=  grayScaleAverage(image);
	cout << "Creating " << grayC->getImageName() <<endl;
	createImageFile(grayC,grayC->getImageName());
	//weighted average
	grayC= grayScaleWeightedAverage(image);
	cout << "Creating " << grayC->getImageName() <<endl;
	createImageFile(grayC,grayC->getImageName());


	//Scaling

	


}
