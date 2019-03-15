#include "ImageProcess.h"


int main(int argc, char *argv[]){

//ifstream file;
 //file.open(argv[1]);

 
 
 /*string format;
 int cols,rows,size;
 //read meta info  
 file >> format >>cols >> rows >>size;
//unsigned char* h= new unsigned char[5000];
string h;
int count=0;
int max=194*259*3;
while(!file.eof()&&count<max){
file>>h;
for(int i=0;i<h.length()&&count<max;i++){
unsigned char g= h[i];
cout<< g <<" ";
count++;
}
}*/


ImageProcess image(argv[1]);
image.createImageFile(image.greyScaleChannel(RED_CHANNEL));

}