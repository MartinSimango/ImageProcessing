import numpy as np
import cv2

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade= cv2.CascadeClassifier('haarcascade_eye.xml')

term_criteria= (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 1 )
key=0
def setupCamShift(track_window):
    global hsv_roi, roi_hist
    x=track_window[0]
    y=track_window[1]
    w=track_window[2]
    h=track_window[3]
    roi= frame[y:y+h, x: x+w]
    #convert image to hsv
    hsv_roi= cv2.cvtColor(roi,cv2.COLOR_BGR2HSV);
    roi_hist= cv2.calcHist([hsv_roi],[0,1],None,[180,256],[0,180,0,256]) #None for mask and hue is from 0-179 so size of 180
    #normalize histogram
    roi_hist= cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)

cap = cv2.VideoCapture(0)

eyesFound=False

camShiftAct=False #camshift activated


while True:
    ret, frame= cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5) #detect all faces in gray
    eyePairCount=0
    if(not camShiftAct):
        for (x,y,w,h) in faces: # find
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2) #blue rectangle with width of 0
            roi_gray = gray[y:y+h, x:x+w] #location of faces
            roi_color = frame[y:y+h, x:x+w] #location of faces on color
            eyes = eye_cascade.detectMultiScale(roi_gray)
            if(len(eyes)>=2):
                #print("Eyes Found!")
                eyesFound=True
                eyePairCount= eyePairCount+1;
                ex_1,ey_1,ew_1,eh_1= eyes[0] # first eye
                ex_2,ey_2,ew_2,eh_2= eyes[1] # second eye
                cv2.rectangle(roi_color,(ex_1,ey_1),(ex_1+ew_1,ey_1+eh_1),(0,255,0),2) #draw green
                cv2.rectangle(roi_color,(ex_2,ey_2),(ex_2+ew_2,ey_2+eh_2),(0,255,0),2) #draw green
                
                nx= ex_1+ew_1 + 1
                ny= ey_1
                nw= (ex_2-(ex_1+ew_1))
                nh= eh_1
                if(ex_1>ex_2):
                    nw=(ex_1 -(ex_2+ew_2))
                    nx=ex_2+ew_2+1
                cv2.rectangle(roi_color,(nx,ny),(nx+nw,ny+nh),(0,0,255),2) #draw red nose
                track_window=(nx+x,ny+y,nw,nh)
                # cv2.rectange(frame)
        if(eyePairCount==0):
             eyesFound=False
               

    
    if(eyesFound and not camShiftAct): #eyes are found and allow user to press space to start camshift
        if(key==32):
            setupCamShift(track_window) # set up histograms for ROI
            camShiftAct=True
    if(camShiftAct==True):
         #back projection(find where roi is in image)
        #convert frame to hsv
        hsv= cv2.cvtColor(frame,cv2.COLOR_BGR2HSV);
        mask= cv2.calcBackProject([hsv],[0,1],roi_hist,[0,180,0,256],1) #scale =1
        #mask is the part of roi that is on the image

        #filter mask more
        kernel= cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5));
        mask= cv2.filter2D(mask,-1,kernel);
       # _,mask= cv2.threshold(mask,15,255,cv2.THRESH_BINARY)
        ret, track_window=cv2.CamShift(mask,track_window,term_criteria)
        
         #draw the rectangle found by camshift
        pts = cv2.boxPoints(ret)
        pts = np.int0(pts)
        cv2.polylines(frame,[pts],True, [255,0,0], 2)
        cv2.polylines(mask,[pts],True, [255,0,0], 2)

        cv2.imshow('mask',mask);
      #  mask= cv2.merge((mask,mask,mask))
      #  print(cv2.bitwise_and(frame,mask))
      #  result= np.bitwise_and(frame,mask);
      #  cv2.imshow('result',result);
    cv2.imshow('frame',frame)
    key=cv2.waitKey(60) & 0xff

    if key==27:
        break

cap.release()    
cv2.destroyAllWindows()
