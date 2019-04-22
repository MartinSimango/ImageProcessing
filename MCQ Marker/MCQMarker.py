import numpy as np
import cv2
import sys
import math
import operator
from pdf2image import convert_from_path
from rotateMCQ import *

MARKING_BOX_LENGTH=4400
MARKING_BOX_ERROR=10000
UPSIDE_DOWN_BOX_LENGTH=1200
UPSIDE_DOWN_ERROR=300
DISPLAY_WIDTH=500
DISPLAY_HEIGHT=600
HOUGH_RADIUS=15;
SCALE_HEIGHT=1656 
SCALE_WIDTH=1170

#get the template from 2016 (sheet with no filled out answers)
#template_2016 = convert_from_path("MCQ_600dpi_2016.pdf")
template_2016 = convert_from_path("2018.pdf")
template_image= np.array(template_2016[(int)(sys.argv[1])])
#template_image= cv2.imread("rand_45_2.pbm",cv2.IMREAD_COLOR)
#template_image=cv2.resize(template_image,(SCALE_WIDTH,SCALE_HEIGHT))
#outline the image
align_45_box=outline(template_image)
#box_image= cv2.imread("box.png",1)
#features(template_image,box_image)

#get the marking box



#find bottom right corner of marking box
(h, w) = template_image.shape[:2]
#corners= getCorners(align_45_box)
#pts_1=np.float32(corners)
#pts_2= np.float32([[0,0],[w,0],[0,h],[w,h]])
#M= cv2.getPerspectiveTransform(pts_1,pts_2)
#template_image=cv2.warpPerspective(template_image,M,(w,h))

box=findMinCotour(template_image,MARKING_BOX_LENGTH,MARKING_BOX_ERROR,[0,255,0],True,False)



cv2.imshow("template_imagea",cv2.resize(template_image,(500,600)))
corners= getCorners(box)
#see if page is sideways
width=corners[1][0]- corners[0][0]
height= corners[3][1]-corners[1][1]
if(width>height): #page is sideways
    print("Sideways",cv2.ROTATE_90_CLOCKWISE)
    template_image=cv2.rotate(template_image,cv2.ROTATE_90_COUNTERCLOCKWISE)
    outline(template_image)
    box=findMinCotour(template_image,MARKING_BOX_LENGTH,MARKING_BOX_ERROR,[0,255,0],True,False)
    corners= getCorners(box) 
    #cv2.imshow("template",cv2.resize(template_image,(500,600)))

#determine if the box is upsideDown or not
(h, w) = template_image.shape[:2]
#get upsideDownBox
topBoxes =findMinCotour(template_image,UPSIDE_DOWN_BOX_LENGTH,UPSIDE_DOWN_ERROR,[0,255,0],True,True) 
cv2.imshow("template",cv2.resize(template_image,(500,600)))
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

print("Cropped: ",cropped.shape[:2])
#cv2.imshow("image",template_image)
#cv2.imshow("rotate",rotated)


#cv2.imshow("cropped1",cv2.resize(cropped,(500,600)))
#rotate page by 180
if(not upRight):
    (h, w) = cropped.shape[:2]
    M = cv2.getRotationMatrix2D((w / 2, h / 2), 180, 1)
    cropped = cv2.warpAffine(cropped, M, (w, h))

cropped= cv2.resize(cropped,(SCALE_WIDTH,SCALE_HEIGHT))
#cv2.imshow("cropped",cv2.resize(cropped,(500,600)))



cropped = cv2.cvtColor(cropped,cv2.COLOR_BGR2GRAY)
img= cv2.GaussianBlur(cropped,(7,7),0) 

#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=14,maxRadius=14)



#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=HOUGH_RADIUS,maxRadius=HOUGH_RADIUS)

#circles = np.uint16(np.around(circles))
#circles=sorted(circles[0,:],key=operator.itemgetter(1,0),reverse=False)
#cv2.circle(img, center, radius, color, thickness=1, lineType=8, shift=0) 
student_count=0;
choice_count=0;
count=0;
fa= open("answers.txt","r")
fs=  open("student_2.txt","r")
lines=fs.readlines()
student_number="g"
task_number=""
for i in range(len(lines)):
    line= lines[i].split()
    if(filled(cropped,int(line[0]),int(line[1]),HOUGH_RADIUS)):
       if(student_count ==5 or student_count==7):
           task_number+=line[2]
       else:
           student_number+=line[2]
       student_count+=1
          
   # print(line[2])

print("Student number: ",student_number)
print("Task number:", task_number)    
    
lines=fa.readlines()
answer= [""]*60
for i in range(len(lines)):
    line= lines[i].split()
    if(filled(cropped,int(line[0]),int(line[1]),HOUGH_RADIUS)):
        answer[int(line[2])-1]+=(line[3])
print("Answers",answer)
cv2.imshow("detected",cv2.resize(cropped,(DISPLAY_WIDTH,DISPLAY_HEIGHT)))
fa.close()
fs.close()
cv2.waitKey(0)
cv2.destroyAllWindows()