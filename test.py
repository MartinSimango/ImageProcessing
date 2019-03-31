import cv2;

img= cv2.imread('bottles.ppm')
cv2.imshow('bottles',img)

cv2.waitKey(0);
cv2.destroyAllWindows();
