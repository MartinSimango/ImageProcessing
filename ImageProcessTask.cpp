#include "MyOpenCV.h"
#include <string>

using namespace mycv;

int main(int argc, char *argv[]){
     
	 //GrayScale 
	Image *image =  imageRead(argv[1]);
	CVImageShow(image->getImageName(),image);
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

	//delete image;

	//Scaling
	Image *scale;
	int w= image->getWidth()*2;
	int h= image->getHeight()*2;
	//nearest neighbour
	
 	scale= scaleNearestNeighbour(image, new Size(w,h));
	cout << "Creating " << scale->getImageName() <<endl;
	createImageFile(scale,scale->getImageName());
	
	//scaling interpolation 
	scale = scaleInterpolation(image,new Size(w,h));
     cout << "Creating " << scale->getImageName() <<endl;
	createImageFile(scale,scale->getImageName());

	string sz= "("+to_string(scale->getWidth())+"x"+to_string(scale->getHeight())+")";
	CVImageShow(scale->getImageName()+sz,scale);
	    cv::waitKey(0);
         cv::destroyAllWindows();
        




	


}
