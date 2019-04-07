import cv2
import numpy as np
import sys

original_img= cv2.imread(sys.argv[1])
secret_img=  cv2.imread(sys.argv[2])
message=""
diff=np.bitwise_xor(original_img,secret_img)
height= len(diff)
width = len(diff[0])
count = 0 # where the next letter wil start

row=0
col=0
pixel=0

while row<height :
    count=0
    bits= []
    for i in range(0,4):
        if(diff[row][col][pixel]==0):
            count=count+1;
        bits.append((secret_img[row][col][pixel] &0x3) <<(-2*i)+6) # get last 2 digits and shift them
        if(pixel==2):
            col=col+1
        if(col==width):
            col=0
            row=row+1
        pixel= (pixel+1) %3
        #now get the character
    if count==4: # read 4 zero's in a row
        break
    character=bits[0]
    for bit_pair in bits:
        character =  character | bit_pair
    character=chr(character)
    message= message + character



print("Hidden message - '", message,"'")


