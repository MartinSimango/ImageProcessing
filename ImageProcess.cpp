#include "ImageProcess.h"

 


Image* ImageProcess::grayScaleChannel(enum Channel channel){
  
  string colors[]= {"RED","GREEN","BLUE"};

  string greyImageName= colors[channel] +image->getImageName();
 //  cout << image->getImageArray()[i][j].rgb[0] << " " <<image->getImageArray()[i][j].rgb[1] << image->getImageArray()[i][j].rgb[2]<<" ";
  Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getRows(),image->getCols(),image->getSize());

  for(int i=0;i<image->getRows();i++){  //divide by 3 as we are going through pixel by pixel and not color by color
    for(int j=0;j<image->getCols();j++){
       
        unsigned char * rgb =image->getPixel(i,j);
        unsigned char grayC= rgb[channel];
        
        retImage->setPixel(i,j,grayC,grayC,grayC);
        delete  [] rgb;
    }
    
}
   
    return retImage;
}

Image * ImageProcess::grayScaleAverage(){
    string greyImageName= "averageGrey" +image->getImageName();
    Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getRows(),image->getCols(),image->getSize());
    for(int i=0;i<image->getRows();i++){  //divide by 3 as we are going through pixel by pixel and not color by color
    for(int j=0;j<image->getCols();j++){
       
        unsigned char * rgb =image->getPixel(i,j);
        unsigned char average = (unsigned char) (((int)rgb[0]+(int)rgb[1]+(int)rgb[2])/3);
        retImage->setPixel(i,j,average,average,average);
        delete  [] rgb;
    }
    
}
   
    return retImage;


}

Image * ImageProcess::grayScaleWeightedAverage(){
    string greyImageName= "weightedGrey" +image->getImageName();
    Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getRows(),image->getCols(),image->getSize());
    for(int i=0;i<image->getRows();i++){  //divide by 3 as we are going through pixel by pixel and not color by color
    for(int j=0;j<image->getCols();j++){
       
        unsigned char * rgb =image->getPixel(i,j);
        int gray= 0.3*(int)rgb[0]+0.59*(int)rgb[1]+0.11*(int)rgb[2];
        retImage->setPixel(i,j,gray,gray,gray);
        delete  [] rgb;
    }
    
}
   
    return retImage;


}


void ImageProcess::createImageFile(Image* im,string filename) const{//create in image file from Image
    ofstream file;
    file.open(filename,ios::binary|ios::out);
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
