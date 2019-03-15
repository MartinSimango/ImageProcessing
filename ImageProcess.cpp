#include "ImageProcess.h"

 


Image* ImageProcess::greyScaleChannel(enum Channel channel){
  
  string colors[]= {"RED","GREEN","BLUE"};

  string greyImageName= colors[channel] +image->getImageName();
 //  cout << image->getImageArray()[i][j].rgb[0] << " " <<image->getImageArray()[i][j].rgb[1] << image->getImageArray()[i][j].rgb[2]<<" ";
  Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getRows(),image->getCols(),image->getSize());

  for(int i=0;i<image->getRows();i++){  //divide by 3 as we are going through pixel by pixel and not color by color
    for(int j=0;j<image->getCols();j++){
       
        unsigned char * rgb =image->getPixel(i,j);
        //cout << rgb[channel]<<rgb[channel]<<rgb[channel];
        unsigned char greyC= rgb[channel];
        
        retImage->setPixel(i,j,greyC,greyC,greyC);
        delete  [] rgb;
    }
    
}
   
    return retImage;
}

void ImageProcess::createImageFile(Image* im) const{//create in image file from Image
    ofstream file;
    file.open(im->getImageName(),ios::binary|ios::out);
     if(!file.is_open()){
        cerr<< "Failed to open " << im->getImageName()<< endl;
        exit(1);
 }


    file << im->getImageFormat() <<endl <<im->getCols() <<" " <<im->getRows() <<"\n" <<im->getSize() << endl;

    for(int i=0;i<im->getRows();i++){
        for(int j=0;j<im->getCols();j++){
            
            // file << (int)im->getImageArray()[i][j].rgb[0]<<" "<<(int) im->getImageArray()[i][j].rgb[1]<<" "<<(int)im->getImageArray()[i][j].rgb[2]<<" " ;
             unsigned char * rgb =im->getPixel(i,j); 
             file << rgb[0]<<rgb[1]<<rgb[2];

       
        }
    }



}
