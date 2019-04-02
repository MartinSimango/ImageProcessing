#include "MyOpenCV.h"
#include <opencv4/opencv2/opencv.hpp>
#include <string>

using namespace mycv;

void showImage(Image * image);
void createFile(Image *image);

int main(int argc, char *argv[]){
     
	
	Image *image =  imageRead(argv[1]);
	showImage(image);
	
	
	//*********************************GrayScale******************************
	/*Image *grayC;
	//single channel
	grayC = grayScaleChannel(image,(Channel)(atoi(argv[2])));
	createFile(grayC);
	showImage(grayC);
    // average grayScale
	grayC= grayScaleAverage(image);
	createFile(grayC);
	showImage(grayC);	
	//weighted average
	grayC= grayScaleWeightedAverage(image);
	createFile(grayC);
	showImage(grayC);	
	

	cv::waitKey(0);
	cv::destroyAllWindows();

	

	//*********************************Scaling******************************
	showImage(image);
	Image *scale;
	int w= image->getWidth()*2;
	int h= image->getHeight()*2;
	//nearest neighbour
	
 	scale= scaleNearestNeighbour(image, new Size(w,h));
	createFile(scale);
	showImage(scale);	
	
	//scaling interpolation 
	scale = scaleInterpolation(image,new Size(w,h));
    createFile(scale);
	showImage(scale);	
	*/

	//Rotation
	Image * rotation= rotate(image,45);
	createFile(rotation);
	showImage(rotation);

	
	
	cv::waitKey(0);
	cv::destroyAllWindows();
	
	
   
	
        

	
}
void createFile(Image *image){
	cout << "Creating " << image->getImageName() <<endl;
	createImageFile(image,image->getImageName());
	
}

void showImage(Image * image){
	string windowName= image->getImageName() + "("+to_string(image->getWidth())+"x"+to_string(image->getHeight())+")";
	cv::Mat im= imread(image->getImageName(),cv::IMREAD_COLOR);
	cv::imshow(windowName,im);
}
