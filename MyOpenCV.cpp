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
    int getMin(int val,int wh,int min){ //helper function
        if(val<wh && val>=0){
            return min;
        }
        if(val<0 && abs(val)>abs(min)){   
            return val;
        }
        
        if(val>wh && abs(val-wh)>abs(min)){     
            return val-(wh-1); //(wh-1 because computer starts counting at 0 so width or height only has 1 less indices e.g. 259 height =258 max value of height for array)
        }
        
        return min;
    }

     Image * rotate(Image *image,double angle ,int about_x, int about_y){
         //rotate about about_x and about_y
           
         double rads= angle* M_PI/180;
        
         //new image size after rotation
         
         //new image dimension
        int newWidth = ceil(abs(image->getHeight()*sin(rads))+abs(image->getWidth()*cos(rads)));
        int newHeight = ceil(abs(image->getWidth()*sin(rads))+ abs(image->getHeight()*cos(rads)));
         string newImageName = "Rotate("+to_string(angle)+")" + image->getImageName();

         //The rotation matrix
         // [ cos(𝜃) -sin(𝜃) (-𝑥⋅cos(𝜃) +𝑦⋅sin(𝜃)+𝑥)] 
         // [ sin(𝜃) cos(𝜃) (−𝑥⋅sin(𝜃) −𝑦⋅cos(𝜃)+𝑦)]
         
         //see check which corner is out of bounds and then adjust rotated image according to which corner
         //was rotated most out of bounds with the image dimension
         int minXCorner=0;
         int minYCorner=0;

         //top left corner
         int topLeftCornerX= ceil(-about_x*cos(rads)+about_y*sin(rads)+about_x);
         minXCorner= getMin(topLeftCornerX,newHeight,minXCorner);
         int topLeftCornerY= ceil(-about_x*sin(rads)-about_y*cos(rads)+about_y);
         minYCorner= getMin(topLeftCornerY,newWidth,minYCorner); 
         
         //top right corner
         int topRightCornerX = ceil(-(image->getWidth()-1)*sin(rads)- about_x*cos(rads)+about_y*sin(rads)+about_x);
         minXCorner= getMin(topRightCornerX,newHeight,minXCorner);
         int topRightCornerY =  ceil((image->getWidth()-1)*cos(rads)- about_x*sin(rads)-about_y*cos(rads)+about_y);
         minYCorner= getMin(topRightCornerY,newWidth,minYCorner); 

         //bottom left corner
         int bottomLeftCornerX= ceil((image->getHeight()-1)*cos(rads) - about_x*cos(rads)+about_y*sin(rads)+about_x);
         minXCorner= getMin(bottomLeftCornerX,newHeight,minXCorner);
         int bottomLeftCornerY= ceil((image->getHeight()-1)*sin(rads)- about_x*sin(rads)-about_y*cos(rads)+about_y);
         minYCorner= getMin(bottomLeftCornerY,newWidth,minYCorner); 
         
         //bottom right corner
         int bottomRightCornerX = ceil((image->getHeight()-1)*cos(rads)-(image->getWidth()-1)*sin(rads)- about_x*cos(rads)+about_y*sin(rads)+about_x);
         minXCorner= getMin(bottomRightCornerX,newHeight,minXCorner);
         int bottomRightCornerY = ceil((image->getHeight()-1)*sin(rads) + (image->getWidth()-1)*cos(rads)- about_x*sin(rads)-about_y*cos(rads)+about_y);
         minYCorner= getMin(bottomRightCornerY,newWidth,minYCorner); 
        
      
        Image *retImage = new Image(newImageName,image->getImageFormat(),newHeight,newWidth,image->getSize());
           
         
        
  
       for(int i=0;i<newHeight;i++){
             for(int j=0;j<newWidth;j++){
                 //get the point it maps to on the original image
                int oldX= ceil((i+minXCorner)*cos(-rads)-(j+minYCorner)*sin(-rads) - about_x*cos(-rads)+about_y*sin(-rads)+about_x);
                int oldY= ceil((i+minXCorner)*sin(-rads)+(j+minYCorner)*cos(-rads) - about_x*sin(-rads)-about_y*cos(-rads)+about_y); 
                //only set the pixel if it maps to an actual point in the original image
               
                if(oldX >=0 && oldX<image->getHeight() && oldY >=0 && oldY<image->getWidth()){
                    unsigned char * rgb =image->getPixel(oldX,oldY);
                    retImage->setPixel(i,j,rgb[0],rgb[1],rgb[2]); 
                    delete [] rgb;
             }
          
         }
       }
         //smoothing edges
        
    
         return retImage;
     }
    Image * rotate(Image *image,double angle ){
        int scaleFactor=5;
        double scaleWidth=image->getWidth()*scaleFactor;
        double scaleHeight=image->getHeight()*scaleFactor;
        int about_x= round(scaleHeight/2.0);
        int about_y= round(scaleWidth/2.0);
        if(angle== ceil(angle) && int(abs(angle))%90==0)
            return rotate(image,angle,round(image->getWidth()/2),round(image->getHeight()/2));
        //small pictures aren't good for rotation cause of straight lines
       // therefore make image bigger than scale back done
        Image * retImage= scaleInterpolation(image,new Size(scaleWidth,scaleHeight));
        //work out scale facters
        double widthSF=scaleWidth/image->getWidth();
        double heightSF=scaleHeight/ image->getHeight();
        //rotate scaled image
        retImage->setImageName(image->getImageName());
        retImage= rotate(retImage,angle,about_x,about_y);
        //scale back down
        string name= retImage->getImageName();
        retImage =scaleInterpolation(retImage,new Size(retImage->getWidth()/scaleFactor,retImage->getHeight()/scaleFactor));
        retImage->setImageName(name); 
        return retImage;
       

    }
    
    //**********************Background Substraction********************************
    cv::Mat subtractFrame(cv::Mat image_1, cv::Mat image_2, int threshold){ //helper function return image 1 vs image 2
    unsigned char *input_1 = (unsigned char*)(image_1.data);
    unsigned char * input_2 = (unsigned char *) (image_2.data);
    cv::Mat retImage= image_1.clone();
    int r,g,b;
    int j,i; 
    for( j = 0;j < image_1.rows;j++){
        for( i = 0;i < image_1.cols;i++){
            //cout << i <<"," <<j <<endl;

            b = abs(input_1[image_1.step * j + (i*3) ] -  input_2[image_2.step *j +i*3]);
            g = abs(input_1[image_1.step * j + (i*3) + 1] - input_2[image_2.step *j +(i*3)+1]);
            r = abs(input_1[image_1.step * j + (i*3) + 2] - input_2[image_2.step *j +(i*3)+2]);
          
           
             int sum= 0.3*(int)r+0.59*(int)g+0.11*(int)b; //weighted average
            if(sum<=threshold){
                retImage.data[image_1.step *j+i*3] =(unsigned char)0;
                retImage.data[image_1.step *j+(i*3)+1]=(unsigned char)0;
                retImage.data[image_1.step *j+(i*3)+2]=(unsigned char)0;
            }
            else{
               retImage.data[image_1.step *j+(i*3)] = (unsigned char)255;
               retImage.data[image_1.step *j+(i*3)+1]=(unsigned char)255;
               retImage.data[image_1.step *j+(i*3)+2]=(unsigned char)255; 
            }
            }
        }
    return retImage;
    }
    void backgroundSubstraction(int threshold){
           cv::VideoCapture cap(0);
           if(!cap.isOpened()){
               cerr << "Failed to open camera! "<<endl;
               return;
           } 

       //    cv::Mat edges;
         //  cv::namedWindow("edges",1);
        cv::Mat background; //read first frame
        cap>>background; //get frame from camera
       // cv::waitKey(30);
           while(1){
               cv::Mat frame;
               cap>>frame; //get frame from camera
            
               if(frame.empty()) break;
               frame= subtractFrame(frame,background,threshold);
               cv::imshow("Background subtraction ",frame);
               if((char) cv::waitKey(30)>=0) break;
               

           }
        
           


    }

    void frameDifference(int threshold){
         cv::VideoCapture cap(0);
           if(!cap.isOpened()){
               cerr << "Failed to open camera! "<<endl;
               return;
           } 

       
        cv::Mat prevFrame; //read first frame
     
        cap>> prevFrame; //get frame from camera
       // cv::waitKey(30);
           while(1){
               cv::Mat frame;
               
               cap>>frame; //get frame from camera
               if(frame.empty()) break;
               cv::Mat diff_frame= subtractFrame(frame,prevFrame,threshold);
               cv::imshow("Frame Differencing ",diff_frame);
               prevFrame=frame.clone();
               if((char) cv::waitKey(60)>=0) break;
               

           } 
    }
    cv::Mat createMovingAverageBackground(cv::Mat image_1, cv::Mat image_2,float a){

        unsigned char *input_1 = (unsigned char*)(image_1.data);
        unsigned char * input_2 = (unsigned char *) (image_2.data);
        cv::Mat retImage= image_1.clone();
        for( int j = 0;j < image_1.rows;j++){
            for( int i = 0;i < image_1.cols;i++){
                retImage.data[image_1.step *j+(i*3)]  =  a*input_1[image_1.step *j+(i*3)]+ (1-a)*input_2[image_1.step *j+(i*3)]; 
                retImage.data[image_1.step *j+(i*3)+1]= a*input_1[image_1.step *j+(i*3)+1]+(1-a)*input_2[image_1.step *j+(i*3)+1];
                retImage.data[image_1.step *j+(i*3)+2]= a*input_1[image_1.step *j+(i*3)+2]+(1-a)*input_2[image_1.step *j+(i*3)+2];
              
                }
            }
    
    return retImage; 

    }
    void runningAverage(int threshold,float learningRate){
         
         cv::VideoCapture cap(0);
           if(!cap.isOpened()){
               cerr << "Failed to open camera! "<<endl;
               return;
           } 

       
        cv::Mat background; //read background
     
        cap>> background; //get frame from camera
        
       
       // cv::waitKey(30);
           while(1){
               cv::Mat frame;
               
               cap>>frame; //get frame from camera
               if(frame.empty()) break;
               
               background= createMovingAverageBackground(frame,background,learningRate);
               cv::Mat diff_frame=subtractFrame(frame,background,threshold);
               cv::imshow("Running average ",diff_frame);
               if((char) cv::waitKey(60)>=0) break;
               

           } 
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
