import cv2
import numpy as np
import sys

img =cv2.imread(sys.argv[1])
cv2.imshow("Original Image",img);
height= len(img)
width = len(img[0])
values= []
for x in sys.argv[2]:
    values.append(ord(x)); # get the ascii values from the image


row=0
col=0
pixel_num=0
for ch in values :
    #seperate byte into groups of 2 bits for each character
    bits=[]
    bits.append((ch & 0xc0)>>6)  #get first 2 bits 
    bits.append((ch &0x30)>>4) #get second 2 bits
    bits.append((ch & 0xc)>>2) #get third 2 bits
    bits.append(ch & 0x3) # get last 2 bits)
    
    for bit in bits:
        img[row][col][pixel_num]= (img[row][col][pixel_num] & 0xfc ) | bit  # replace last 2 bits of pixel
        if(pixel_num==2):
            col=col+1
        pixel_num = (pixel_num+1) %3
        if(col==width):
            col=0
            row=row+1
        if(row==height):
            print("Image is not big enough to hold your image")
            exit(-1);
   

    

    
cv2.imshow("Hidden Image",img);

cv2.imwrite("Hide_"+sys.argv[1],img);
cv2.waitKey(0);
