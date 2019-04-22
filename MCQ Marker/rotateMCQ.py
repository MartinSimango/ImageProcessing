#this scripts returns the rotatate
import numpy as np
import cv2



    
def boxContour(contour,sheet,color,draw):
    rect= cv2.minAreaRect(contour)
    box = cv2.boxPoints(rect)
    box=np.int0(box)
    if(draw):
        cv2.polylines(sheet,[box],True, color, 2)
    return box


def outline(sheet): #this function will outline the page with black
    gray_sheet= cv2.cvtColor(sheet,cv2.COLOR_BGR2GRAY)
    cv2.imshow("am",cv2.resize(gray_sheet,(500,600)))
    gray_sheet=cv2.merge((gray_sheet,gray_sheet,gray_sheet))
    roi= gray_sheet[0:1, 0: 1] #take top left corner
    hsv_roi= cv2.cvtColor(roi,cv2.COLOR_BGR2HSV);
    roi_hist= cv2.calcHist([hsv_roi],[0],None,[180],[0,180]) #None for mask and hue is from 0-179 so size of 180
    #normalize histogram
    roi_hist= cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)
    hsv= cv2.cvtColor(gray_sheet,cv2.COLOR_BGR2HSV);
    mask= cv2.calcBackProject([hsv],[0],roi_hist,[0,180],1) #scale =1
    #back project white(in top left corner of image onto rest of page)
    #this will leave the page black and the surronds of the page white
    _,ma= cv2.threshold(gray_sheet,250,255,0)
    cv2.imshow("m",cv2.resize(ma,(500,600)))
    #smoothing the edges
    #draw a countour round the box and the contours neately
  #  ma= cv2.merge((ma,ma,ma))
    ma=cv2.cvtColor(ma, cv2.COLOR_BGR2GRAY);
    ma=cv2.GaussianBlur(ma,(5,5),11) 
    contours,_=cv2.findContours(ma,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);
    #cv2.drawContours(sheet,contours,-1,[0,0,0],1)
    maxContour=(-1,-1)
    print("sdfg:", len(contours))
    for i in range(1,len(contours)):
       arcLength=cv2.arcLength(contours[i],True)
       if(arcLength>maxContour[0]):
            maxContour=(arcLength,i)    
    print("Max",maxContour)
    return boxContour(contours[maxContour[1]],sheet,[0,0,0],True);
    

    

#will find min Contour of contours between boxLength and boxLength+errorMargin if returnAll=False
# will return all contours  between boxLength and boxLength+errorMargin if returnAll=True 
def findMinCotour(sheet,boxLength,errorMargin,color,draw,returnAll):
    #convert to sheet to grayscale then make it monochrome
    gray_sheet= cv2.cvtColor(sheet,cv2.COLOR_BGR2GRAY)
    ret,thresh= cv2.threshold(gray_sheet,210,255,0)
    contours,_=cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE);

    possible_contours=[]
    minContour = (-1,-1)
    for i in range(len(contours)):
        #removeDup(contours)
        arcLength=cv2.arcLength(contours[i],True)
        if(arcLength>boxLength and arcLength<boxLength+errorMargin):  #only dray contours with greater than this length
            #cv2.drawContours(sheet,[contours[i]],0,(0,255,0),3)
            if(returnAll):
                possible_contours.append(boxContour(contours[i],sheet,color,draw))

            if(minContour == (-1,-1)):
                minContour = (arcLength,i);
            elif(arcLength<minContour[0]):
                minContour=(arcLength,i)
          
    if(returnAll):
        return possible_contours
    else:
        print(minContour)
        return boxContour(contours[minContour[1]],sheet,color,draw)
        
def getCorners(box):
    print(box)
    maxSum=0
    index=0
    for i in range(0,4):
        sum=box[i][0]+box[i][1]
        if(sum>maxSum):
            maxSum=sum
            index=i;
    
    BR=box[index]
    BL=box[(index+1)%4]
    TL=box[(index+2)%4]
    TR=box[(index+3)%4]
    return [TL,TR,BL,BR]

#returns if the orientation of page could be found and whether box is upside down 
#o
def findOrientation(topBoxes,corners):
       #determine which side of the page box is on left or right side
    boxTop=0
    boxBot=0;
    halfway= abs(corners[0][0] +corners[1][0])/2
    for boxes in topBoxes:
        
        cor= getCorners(boxes);
        #print("Corners:",cor,corners)
        halfway_small= abs(cor[0][0] +cor[1][0])/2 
        
        print("Right S",corners[2][0],corners[2][1],corners[3][0],corners[3][1])
        print("Right B",cor[0][0],cor[0][1],cor[1][0],cor[1][1])
        if(cor[2][1]<corners[0][1] and cor[3][1]<corners[1][1] ): # 0- TL 1-TR 2-BL 3-BR
                #box is above marking box now check which side
            if(halfway_small <halfway):
                if(corners[0][1]-cor[2][1]<60 and corners[0][1]-cor[3][1]<60):
                        if(cor[0][0]- corners[0][0]<30 and cor[2][0]-corners[0][0]<30):    
                            boxTop+=1;
        elif(cor[0][1]>corners[2][1] and cor[1][1]>corners[3][1]):
                #box is below marking box now check which side
                if(halfway_small >halfway):
                    #print("dsf",cor[0][1],corners[2][1],corners[3][1])
                    if(cor[0][1]-corners[2][1]<60 and cor[1][1]-corners[3][1]<60):
                        if(corners[3][0]-cor[1][0] <30 and cor[3][0]-corners[3][0]<30):    
                            boxBot+=1;
    print("Out",boxTop,boxBot)
    if(boxTop>0 and boxBot==0): #box is on top therefore page=upright
        return (True,True) #orientation found and box is upright
    if(boxTop==0 and boxBot>0):
        return (True,False)
    else:
        return (False,False)
'''
def features(template_image,box_image):
      gray_temp= cv2.cvtColor(template_image,cv2.COLOR_BGR2GRAY)
      gray_box = cv2.cvtColor(box_image,cv2.COLOR_BGR2GRAY)
     # _,gray_box= cv2.threshold(gray_box,210,255,0)
      #_,gray_temp= cv2.threshold(gray_temp,210,255,0)
      #ORB Detector
      orb= cv2.ORB_create()
      kp1, des1= orb.detectAndCompute(gray_temp,None)
      kp2, des2= orb.detectAndCompute(gray_box,None)
    
      bf= cv2.BFMatcher(cv2.NORM_HAMMING,crossCheck=True)
      matches= bf.match(des1,des2)
      matches= sorted(matches,key=lambda x:x.distance)
      print(len(matches))
      

      result= cv2.drawMatches(gray_temp,kp1,gray_box,kp1,matches[:15],None,flags=2);
      result=cv2.resize(result,(400,700))
      cv2.imshow("matches",result);
      cv2.waitKey(0)
      cv2.destroyAllWindows();
     #     print(d)
  #  cv2.imshow()    
   # cv2.imw  
'''
#returns whether circle is filled in and what circle is colored in
def filled(cropped,x,y,radius):
    count=0
    points= radius*7*8
    for j in range(7):
        for k in range(radius): 
            if(cropped[y+k][x+j]<200):
                count+=1;
            if(cropped[y+k][x-j]<200):
                count+=1;
            if(cropped[y+j][x+k]<200):
                    count+=1;
            if(cropped[y+j][x-k]<200):
                count+=1;
            if(cropped[y-k][x-j]<200):
                count+=1;
            if(cropped[y-k][x+j]<200):
                count+=1;
            if(cropped[y-j][x-k]<200):
                count+=1;
            if(cropped[y-j][x+k]<200):
                count+=1;
    #print("Count: ",count)
    return count>(points/2) #must have atleast have the points shaded in