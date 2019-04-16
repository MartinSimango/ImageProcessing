import cv2
import sys
import numpy as np


#get two pictures
image_1=cv2.imread(sys.argv[1])
image_2= cv2.imread(sys.argv[2])
original_image_and= np.bitwise_and(image_1,image_2);
#original_image_xor= np.invert(cv2.bitwise_xor(image_1,image_2))
cv2.imshow('Original',original_image_and)
#cv2.imshow('Original(XOR) ',original_image_xor)
cv2.waitKey(0)
cv2.destroyAllWindows()