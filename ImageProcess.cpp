#include "ImageProcess.h"

 


Image* ImageProcess::greyScaleChannel(enum Channel channel){
  
  string colors[]= {"RED","GREEN","BLUE"};

  string greyImageName= colors[channel] +image->getImageName();
  
  Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getRows(),image->getCols(),image->getSize());

  for(int i=0;i<image->getRows();i++){  //divide by 3 as we are going through pixel by pixel and not color by color
    for(int j=0;j<image->getCols();j++){
        int * rgb =image->getPixel(i,j);
        int greyC= rgb[channel];
        retImage->setPixel(i,j,greyC,greyC,greyC);
        delete  [] rgb;
    }
    
}

   
    return retImage;
}

void ImageProcess::createImageFile(Image* im) const{//create in image file from Image
    ofstream file;
    file.open(im->getImageName());
     if(!file.is_open()){
        cerr<< "Failed to open " << im->getImageName()<< endl;
        exit(1);
 }

    file << im->getImageFormat() <<endl <<im->getCols() <<" " <<im->getRows() <<"\n" <<im->getSize() << endl;
    for(int i=0;i<im->getRows();i++){
        for(int j=0;j<im->getCols();j++){
             file << im->getImageArray()[i][j].red<<" " << im->getImageArray()[i][j].green<< " "<<im->getImageArray()[i][j].blue<<" ";
        }
    }



}
