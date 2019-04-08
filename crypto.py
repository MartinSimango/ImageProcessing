import cv2
import numpy as np
import random as rand
import sys
#define combinations

img=cv2.imread("chess.png",0) #read in the picture as a gray scale

#apply threshhold to image
_,mono= cv2.threshold(img,100,255,cv2.THRESH_BINARY)



#define 4 by 4 pixels transformation
white_pixel_1=[255,0,0,255]
white_pixel_2=[0,255,255,0]
WPixels=[white_pixel_1,white_pixel_2]

black_pixel_1=white_pixel_1
black_pixel_1_pair= white_pixel_2
black_pixel_2=white_pixel_2
black_pixel_2_pair=white_pixel_1

BPixels=[black_pixel_1,black_pixel_2]
BPair_Pixels=[black_pixel_1_pair,black_pixel_2_pair]

height=len(mono)
width= len(mono[0]);

#new pictures will be four times as large
newHeight=height*2
newWidth= width*2



#the two new images
mono_pic_1=  cv2.resize(mono,(newWidth,newHeight))
mono_pic_2 = cv2.resize(mono,(newWidth,newHeight)) 

for i in range(height):
    for j in range(width):
        #what pair is going to be used
        pair=1
        if(rand.randint(1,10)<=5):
            pair=0
        if(mono[i][j]==0):# pixel is black 
            #set the next four pixels of the two new images
            for row in range(2):
                for col in range(2):
                    mono_pic_1[(2*i)+row][(2*j)+col]= WPixels[pair][row*2+col] #white=0 and black=1 so need to swap meaning of 255 and 0 around
                    mono_pic_2[(2*i)+row][(2*j)+col] = WPixels[pair][row*2+col]
        else:  #pixel is white
            for row in range(2):
                for col in range(2):
                    mono_pic_1[(2*i)+row][(2*j)+col]= BPixels[pair][row*2+col]
                    mono_pic_2[(2*i)+row][(2*j)+col] = BPair_Pixels[pair][row*2+col]

cv2.imshow('mono',mono)

#cv2.imshow('mono_1', mono_pic_1)
#cv2.imshow('mono_2',mono_pic_2)
cv2.imwrite("chess_1.png",mono_pic_1)
cv2.imwrite("chess_2.png",mono_pic_2)

cv2.waitKey(0)
cv2.destroyAllWindows()

