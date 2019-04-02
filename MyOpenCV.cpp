#include "MyOpenCV.h"


using namespace std;
namespace mycv{


    Image * imageRead(string imageName){
    
    return new Image(imageName);

    }

    //**********************GRAYSCALE********************************
    Image* grayScaleChannel(Image *image,enum Channel channel){
    
    string colors[]= {"RED","GREEN","BLUE"};

    string greyImageName= colors[channel] + image->getImageName();
    Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());

    for(int i=0;i<image->getHeight();i++){ 
            for(int j=0;j<image->getWidth();j++){
            unsigned char * rgb =image->getPixel(i,j);
            unsigned char grayC= rgb[channel];
            
            retImage->setPixel(i,j,grayC,grayC,grayC);
            delete  [] rgb;
        }
    }
        return retImage;
    }

    Image * grayScaleAverage(Image *image){
        string greyImageName= "averageGrey" +image->getImageName();
        Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());
        for(int i=0;i<image->getHeight();i++){  
            for(int j=0;j<image->getWidth();j++){
        
                unsigned char * rgb =image->getPixel(i,j);
                unsigned char average = (unsigned char) (((int)rgb[0]+(int)rgb[1]+(int)rgb[2])/3);
                retImage->setPixel(i,j,average,average,average);
                delete  [] rgb;
        }
        
    }
        return retImage;

    }

    Image * grayScaleWeightedAverage(Image *image){
        string greyImageName= "weightedGrey" +image->getImageName();
        Image *retImage = new Image(greyImageName,image->getImageFormat(),image->getHeight(),image->getWidth(),image->getSize());
        for(int i=0;i<image->getHeight();i++){ 
            for(int j=0;j<image->getWidth();j++){
                unsigned char * rgb =image->getPixel(i,j);
                int gray= 0.3*(int)rgb[0]+0.59*(int)rgb[1]+0.11*(int)rgb[2];
                retImage->setPixel(i,j,gray,gray,gray);
                delete  [] rgb;
        }
        
    }
    
        return retImage;

    }

     //**********************SCALING********************************
    Image * scaleNearestNeighbour(Image *image,Size * newSize){ //enter  new size
        string newImageName = "ResizeNearest"+image->getImageName(); 
        Image *retImage = new Image(newImageName,image->getImageFormat(),newSize->height,newSize->width,image->getSize());
 
        int x_ratio = (int)((image->getWidth()<<16)/newSize->width) +1;
        int y_ratio = (int)((image->getHeight()<<16)/newSize->height) +1;
    
        int x2, y2 ;
    
        for(int i=0;i<retImage->getHeight();i++){
            for(int j=0;j<retImage->getWidth();j++){
                 x2 = ((j*x_ratio)>>16);
                 y2 = ((i*y_ratio)>>16);
                
                 unsigned char * rgb = image->getPixel(y2,x2);
                 retImage->setPixel(i,j,rgb[0],rgb[1],rgb[2]);
                 delete [] rgb; //free memoery
                //insert code here
            }
        }

        return retImage;


    }
    Image * scaleInterpolation(Image *image,Size * newSize){ //enter  new size
        string newImageName = "ResizeInterpolation"+image->getImageName(); 
        //create empty image
        Image *retImage = new Image(newImageName,image->getImageFormat(),newSize->height,newSize->width,image->getSize());
        
        int x,y;
        float x_ratio = ((float)(image->getWidth()-1))/newSize->width ;
        //the -1 takes care of the egde case of x+1 going over the array bounds
        float y_ratio = ((float)(image->getHeight()-1))/newSize->height;

        float x_diff, y_diff, blue, red, green ;
        int offset = 0 ;
        for(int i=0;i<retImage->getHeight();i++){
            for(int j=0;j<retImage->getWidth();j++){
                x= (int)(x_ratio *j);
                y= (int)(y_ratio *i);
                x_diff=(x_ratio*j)-x; //decimal difference e.g 5.6 -5=0.6
                y_diff = (y_ratio*i) -y;
                
                //get four neighbour
                unsigned char* a = image->getPixel(y,x);
                unsigned char* b = image->getPixel(y,x+1);
                unsigned char* c = image->getPixel(y+1,x);
                unsigned char* d = image->getPixel(y+1,x+1);

                //apply bilinear intepolation
                red= a[0]*(1-x_diff)*(1-y_diff) + b[0]*(x_diff)*(1-y_diff) + c[0]*(y_diff)*(1-x_diff) +d[0]*(x_diff*y_diff);
                green= a[1]*(1-x_diff)*(1-y_diff) + b[1]*(x_diff)*(1-y_diff) + c[1]*(y_diff)*(1-x_diff)+d[1]*(x_diff*y_diff);
                blue= a[2]*(1-x_diff)*(1-y_diff) + b[2]*(x_diff)*(1-y_diff) + c[2]*(y_diff)*(1-x_diff) + d[2]*(x_diff*y_diff);
                
                
                retImage->setPixel(i,j,red,green,blue); //compiler will implicitly cast int to unsinged char
                //free memory
                delete [] a;
                delete [] b;
                delete [] c;
                delete [] d;

            }
        }
        return retImage;


    }
 //**********************ROTATION********************************
     Image * rotate(Image *image,double angle ,double about_x, double about_y){
         //rotate about about_x and about_y
         string newImageName = "Rotate("+to_string(angle)+","+to_string(about_x)+","+to_string(about_y)+")" + image->getImageName();
         double rads= angle* M_PI/180;
        
         //new image size after rotation
         
         //new image dimension
         int newWidth = abs(image->getHeight()*sin(rads) +image->getWidth()*cos(rads));
         int newHeight = abs(image->getWidth()*sin(rads)+ image->getHeight()*cos(rads));

         //The rotation matrix
         // [ cos(𝜃) -sin(𝜃) (-𝑥⋅cos(𝜃) +𝑦⋅sin(𝜃)+𝑥)] 
         // [ sin(𝜃) cos(𝜃) (−𝑥⋅sin(𝜃) −𝑦⋅cos(𝜃)+𝑦)]
         
         //see where corners are adjusted to
         int leftCornerX= - about_x*cos(rads)+about_y*sin(rads)+about_x;
         int leftCornerY= - about_x*sin(rads)-about_y*cos(rads)+about_y;
         int rightCornerX = -image->getWidth()*sin(rads)- about_x*cos(rads)+about_y*sin(rads)+about_x;
         int rightCornerY =  image->getWidth()*cos(rads)- about_x*sin(rads)-about_y*cos(rads)+about_y;
          
         int minY=0;
         int minYPair=1000000;
         int minX=0;
         int minXPair=1000000;
         int xi , xj;
         int yi, yj;
        
         cout << newWidth << "X" <<newHeight<<endl;
         Image *retImage = new Image(newImageName,image->getImageFormat(),newHeight,newWidth,image->getSize());
         for(int i=0;i< image->getHeight();i++){
             for(int j=0;j<image->getWidth();j++){
                 int newX= i*cos(rads)-j*sin(rads)- about_x*cos(rads)+about_y*sin(rads)+about_x-rightCornerX;
                 int newY= i*sin(rads)+j*cos(rads) - about_x*sin(rads)-about_y*cos(rads)+about_y-leftCornerY;
                 
                 if(newX<minX){
                    minX= newX;
                    minXPair= newY;
                    xi=i;
                    xj=j;
                 }
                 if(newY<minY){
                    minY= newY;
                    minYPair= newX;
                    yi=i;
                    yj=j;
                 }
                if(i==0)
                 cout << "("<<i <<","<<j << ") becomes (" << newX <<","<<newY<<")"<<endl;
                // newX= abs(newX);
                 //newY= abs(newY);
                 unsigned char * rgb =image->getPixel(i,j);
              
                 if(newX>=0 && newY>=0 && newX< retImage->getHeight() && newY<retImage->getWidth())
                    retImage->setPixel(newX,newY,rgb[0],rgb[1],rgb[2]);
             
                 delete [] rgb;
             }
         }
            cout << "MinX (" << xi<<","<<xj<<") gets mapped to ("<< minX<<","<<minXPair<<")"<<endl;
            cout << "MinY (" << yi<<","<<yj<<") gets mapped to ("<< minYPair<<","<<minY<<")"<<endl;
            cout << "("<<rightCornerX <<","<<rightCornerY << ") becomes (" <<leftCornerX <<","<<leftCornerY<<")"<<endl;
         return retImage;
     }
    Image * rotate(Image *image,double angle ){

        return rotate(image,angle,image->getWidth()/2,image->getHeight()/2);

    }
    
    
    void createImageFile(Image* im,string filename) {//create in image file from Image
        ofstream file;
        file.open(filename,ios::binary|ios::out);
        if(!file.is_open()){
            cerr<< "Failed to open " << im->getImageName()<< endl;
            exit(1);
    }

        file << im->getImageFormat() <<endl <<im->getWidth() <<" " <<im->getHeight() <<"\n" <<im->getSize() << endl;
        for(int i=0;i<im->getHeight();i++){
            for(int j=0;j<im->getWidth();j++){
                unsigned char * rgb =im->getPixel(i,j); 
                file << rgb[0]<<rgb[1]<<rgb[2];
                //free memory
                delete [] rgb;

        
            }
        }

    }
    

}
