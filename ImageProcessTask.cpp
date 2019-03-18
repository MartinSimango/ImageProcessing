#include "MyOpenCV.h"


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

	delete image;

	//Scaling
	Image *scale;
	//nearest neighbour

 	scale= scaleNearestNeighbour(image, new Size(400,500));
	cout << "Creating " << scale->getImageName() <<endl;
	createImageFile(scale,scale->getImageName());
	//interpolation 
	//scale = scaleInterpolation(image,new Size(100,100));
	//cout << "Creating " << scale->getImageName() <<endl;
	//createImageFile(scale,scale->getImageName());



	


}
