import numpy as np
import cv2
import sys
from pdf2image import convert_from_path


def myarc(cont):
    sum=0;
    points=[];
    for i in range(1,len(cont)):
        x1=cont[i-1][0][0]
        y1=cont[i-1][0][1]
        x2=cont[i][0][0]
        y2=cont[i][0][1]
        if(points.count((x1,y1))==0 and points.count((x2,y2))==0):
    
            points.append((x1,y1))
        
     
            points.append((x2,y2))
        else:
            continue
        
        sum+= np.sqrt(np.square(x2-x1)+np.square(y2-y1))
    x1=cont[0][0][0]
    y1=cont[0][0][1]
    x2=cont[len(cont)-1][0][0]
    y2=cont[len(cont)-1][0][1]
    sum+= np.sqrt(np.square(x2-x1)+np.square(y2-y1))
    return sum

#get the template from 2016 (sheet with no filled out answers)
template_2016 = convert_from_path("MCQ_600dpi_2016.pdf")
#template_2016 = convert_from_path("2018.pdf")
template_image= np.array(template_2016[20])



roi= template_image[0:1, 0: 1] #take top left corner
hsv_roi= cv2.cvtColor(roi,cv2.COLOR_BGR2HSV);

roi_hist= cv2.calcHist([hsv_roi],[0],None,[180],[0,180]) #None for mask and hue is from 0-179 so size of 180
#normalize histogram
roi_hist= cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)
hsv= cv2.cvtColor(template_image,cv2.COLOR_BGR2HSV);
mask= cv2.calcBackProject([hsv],[0],roi_hist,[0,180],1) #scale =1
mask=cv2.GaussianBlur(mask,(5,5),11) 
cv2.imshow('mask',mask);

cv2.waitKey(0);
contours,_=cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
cv2.drawContours(template_image,contours,-1,(0,0,0),2)
cv2.imshow('l',template_image);


template_image_gray= cv2.cvtColor(template_image,cv2.COLOR_BGR2GRAY)
ret,thresh= cv2.threshold(template_image_gray,210,255,0)

contours,_=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
cv2.imshow("thresh",thresh);
cv2.imshow("original",template_image);
#draw all contours
#cv2.drawContours(template_image,contours,-1,0,(0,255,0),3)

possible_contours=[]

for i in range(len(contours)):
    #removeDup(contours)
    arcLength=cv2.arcLength(contours[i],True)
    a= myarc(contours[i]);
    if(a>1500):  #only dray contours with this length
        cv2.drawContours(template_image,[contours[0]],0,(0,255,0),3)
        print(arcLength)
        possible_contours.append([a ,i])
print(len(possible_contours))
print(possible_contours)
#print(contours[0])
#@print(len(cnt))
#print(contours[0][0][0][])
#retval=cv2.arcLength(cnt, True)
#print(retval);


cv2.imshow("contours",template_image);
#img= cv2.GaussianBlur(template_image,(5,5),2) 

#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=14,maxRadius=14)


#images= convert_from_path(sys.argv[1]);
#all images in the pdf
#pages=[]
#for image in images:
#    pages.append(cv2.cvtColor(np.array(image),cv2.COLOR_BGR2GRAY))

#img = cv2.GaussianBlur(pages[0],(5,5),2)
#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=14,maxRadius=14)

#circles = np.uint16(np.around(circles))

#cv2.circle(img, center, radius, color, thickness=1, lineType=8, shift=0) 

#for i in circles[0,:]:
    # draw the outer circle
 #   cv2.circle(pages[0],(i[0],i[1]),i[2],(0,255,0),2)
    # draw the center of the circle

    #cv2.circle(pages[0],(i[0],i[1]),2,(0,0,255),3)
#cv2.imshow('detected circles',pages[0])
#cv2.imshow("image",pages[0])

cv2.waitKey(0)
cv2.destroyAllWindows()