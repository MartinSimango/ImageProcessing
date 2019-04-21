import numpy as np
import cv2
import sys
import math
from pdf2image import convert_from_path
from rotateMCQ import *

MARKING_BOX_LENGTH=4900
MARKING_BOX_ERROR=10000
UPSIDE_DOWN_BOX_LENGTH=1200
UPSIDE_DOWN_ERROR=300
DISPLAY_WIDTH=500
DISPLAY_HEIGHT=600
#get the template from 2016 (sheet with no filled out answers)
template_2016 = convert_from_path("MCQ_600dpi_2016.pdf")
#template_2016 = convert_from_path("2018.pdf")
template_image= np.array(template_2016[(int)(sys.argv[1])])

#outline the image
outline(template_image)
#box_image= cv2.imread("box.png",1)
#features(template_image,box_image)

#get upsideDownBox
#contours,_=cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
topBoxes =findMinCotour(template_image,UPSIDE_DOWN_BOX_LENGTH,UPSIDE_DOWN_ERROR,[0,255,0],True,True) 
#get the marking box
box=findMinCotour(template_image,MARKING_BOX_LENGTH,MARKING_BOX_ERROR,[0,255,0],True,False)


(h, w) = template_image.shape[:2]
print(h,w)
#find bottom right corner of marking box
cv2.imshow("template_image",cv2.resize(template_image,(500,600)))
corners= getCorners(box)
#determine if the box is upsideDown or not
boxFound,upRight=findOrientation(topBoxes,corners)
if(not boxFound): #reject page
    print("Could not find box")
if(upRight):
    print("page is upright!")
else:
    print("page is upside down!")
#print(rect)
# crop out the marking box

pts_1=np.float32(corners)
pts_2= np.float32([[0,0],[w,0],[0,h],[w,h]])

M= cv2.getPerspectiveTransform(pts_1,pts_2)
cropped=cv2.warpPerspective(template_image,M,(w,h))

#cv2.imshow("image",template_image)
#cv2.imshow("rotate",rotated)


#cv2.imshow("cropped1",cv2.resize(cropped,(500,600)))
#rotate page by 180
if(not upRight):
    (h, w) = cropped.shape[:2]
    M = cv2.getRotationMatrix2D((w / 2, h / 2), 180, 1)
    cropped = cv2.warpAffine(cropped, M, (w, h))

#cv2.imshow("cropped",cv2.resize(cropped,(500,600)))

'''
roi= template_image[0:1, 0: 1] #take top left corner
hsv_roi= cv2.cvtColor(roi,cv2.COLOR_BGR2HSV);

roi_hist= cv2.calcHist([hsv_roi],[0],None,[180],[0,180]) #None for mask and hue is from 0-179 so size of 180
#normalize histogram
roi_hist= cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)
hsv= cv2.cvtColor(template_image,cv2.COLOR_BGR2HSV);
mask= cv2.calcBackProject([hsv],[0],roi_hist,[0,180],1) #scale =1
mask=cv2.GaussianBlur(mask,(5,5),11) 


contours,_=cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
rect= cv2.minAreaRect(contours[1])
box = cv2.boxPoints(rect)
box=np.int0(box)
print(box)
cv2.polylines(template_image,[box],True, [0,0,0], 2)

cv2.imshow('tem',template_image);
cv2.waitKey(0);

cv2.imshow('l',template_image);


template_image_gray= cv2.cvtColor(template_image,cv2.COLOR_BGR2GRAY)
ret,thresh= cv2.threshold(template_image_gray,210,255,0)

contours,_=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
cv2.imshow("thresh",thresh);
cv2.imshow("original",template_image);
#draw all contours
#cv2.drawContours(template_image,contours,-1,(0,255,0),3)

possible_contours=[]

for i in range(len(contours)):
    #removeDup(contours)
    arcLength=cv2.arcLength(contours[i],True)
    a= myarc(contours[i]);
    if(arcLength>4356):  #only dray contours with this length
        cv2.drawContours(template_image,[contours[179]],0,(0,255,0),3)
        print(arcLength)
        possible_contours.append([arcLength ,i])
print(len(possible_contours))
print(possible_contours)
#print(contours[0])
#@print(len(cnt))
#print(contours[0][0][0][])
#retval=cv2.arcLength(cnt, True)
#print(retval);

rect= cv2.minAreaRect(contours[179])
box = cv2.boxPoints(rect)
box=np.int0(box)
print(box)
print("rect")
print(rect)
cv2.polylines(template_image,[box],True, [255,0,0], 2)
cv2.imshow("contours",template_image);


(h, w) = template_image.shape[:2]
# calculate the center of the image
center = (w / 2, h / 2)
 
scale = 1
angle= rect[2]
# Perform the counter clockwise rotation holding at the center
# 90 degrees
M = cv2.getRotationMatrix2D(center, angle, scale)
rads= math.radians(angle)
#h= float(h)
#w= float(w)
#width = math.ceil(abs(h*math.sin(rads))+abs(w*math.cos(rads)))
#height =  math.ceil(abs(w*math.sin(rads))+abs(h*math.cos(rads)))

rotated = cv2.warpAffine(template_image, M, (h*2, width*2))

template_image_gray= cv2.cvtColor(rotated,cv2.COLOR_BGR2GRAY)
ret,thresh= cv2.threshold(template_image_gray,210,255,0)

contours,_=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);

possible_contours=[]
for i in range(len(contours)):
    #removeDup(contours)
    arcLength=cv2.arcLength(contours[i],True)
    a= myarc(contours[i]);
    if(arcLength>4356):  #only dray contours with this length
        #cv2.drawContours(rotated,[contours[181]],0,(0,0,255),3)
        print(arcLength)
        possible_contours.append([arcLength ,i])
print(len(possible_contours))
print(possible_contours)
#print(contours[0])
#@print(len(cnt))
#print(contours[0][0][0][])
#retval=cv2.arcLength(cnt, True)
#print(retval);

rect= cv2.minAreaRect(contours[181])
box = cv2.boxPoints(rect)
box=np.int0(box)
print(box)
print("rect")
print(rect)
cv2.polylines(rotated,[box],True, [0,0,255], 2)
cv2.imshow("contours",template_image);
#rotated= rotated[rect[1][1]:rect.height+rect[1][1],rect[1][0]:rect[1][0]+rect.width]
cv2.imshow("rotated",rotated); 

#a
#rotate by angle
'''

cropped = cv2.cvtColor(cropped,cv2.COLOR_BGR2GRAY)
img= cv2.GaussianBlur(cropped,(7,7),2) 

#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=14,maxRadius=14)



circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=15,maxRadius=15)

circles = np.uint16(np.around(circles))

#cv2.circle(img, center, radius, color, thickness=1, lineType=8, shift=0) 

for i in circles[0,:]:
    # draw the outer circle
    #if(i[0]>52 and i[0]<450 and i[1]<1500): #circles for student number
     #   cv2.circle(cropped,(i[0],i[1]),i[2],(0,255,0),2)
    # draw the center of the circle
      #  cv2.circle(cropped,(i[0],i[1]),2,(0,0,255),3)
   # else: 
    if(i[0]>500 and i[1]<1500):
        cv2.circle(cropped,(i[0],i[1]),i[2],(0,255,0),2)
    # draw the center of the circle
        cv2.circle(cropped,(i[0],i[1]),2,(0,0,255),3) 

cv2.imshow("detected",cv2.resize(cropped,(DISPLAY_WIDTH,DISPLAY_HEIGHT)))
#cv2.imshow("image",pages[0])

cv2.waitKey(0)
cv2.destroyAllWindows()