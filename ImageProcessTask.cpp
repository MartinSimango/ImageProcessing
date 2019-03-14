#include "ImageProcess.h"


int main(int argc, char *argv[]){

ImageProcess image(argv[1]);
image.createImageFile(image.greyScaleChannel(RED_CHANNEL));

}