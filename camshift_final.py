import cv2
import numpy as np
ix,iy,jx,jy= -1,-1,-1,-1 # invalid coords to begin with
selected=False
pause=False
def select_ROI(event,x,y,flags,param):
    global ix,iy,jx,jy
    global selected,pause
    if(pause):
        selected=True
    if event == cv2.EVENT_LBUTTONDOWN:
        ix,iy = x,y #starting coords
    elif event == cv2.EVENT_LBUTTONUP:
        jx,jy = x,y #ending coords
        #draw rectangle on frame
        cv2.rectangle(frame,(ix,iy),(jx,jy),(255,0,0),2) 
         

# setup the mouse callback
cv2.namedWindow('frame',cv2.WINDOW_NORMAL) #create namedwindow
# Binding select_ROI with the frame
cv2.setMouseCallback('frame',select_ROI) #create an mouse event on that windo



cap= cv2.VideoCapture(0)


term_criteria= (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 1 )
track = False
while True:
    _, frame= cap.read()
    while(pause): 
        
        cv2.imshow('frame',frame) #keep showing the current frame until rectangle is drawn on object
       
        if((cv2.waitKey(1) & 0xff) == 32):
            pause = False #unpause
            if(selected):
                track=True
                r,h,c,w = iy , abs((jy-iy)) , ix , abs((jx-ix))
                track_window = (c,r,w,h) #set up the tracking window
                roi= frame[iy:iy+h, ix: ix+w]
                #convert image to hsv
                hsv_roi= cv2.cvtColor(roi,cv2.COLOR_BGR2HSV);
                roi_hist= cv2.calcHist([hsv_roi],[0,1],None,[180,256],[0,180,0,256]) #None for mask and hue is from 0-179 so size of 180
                #normalize histogram
                roi_hist= cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)

               

    if track==True:
        #back projection(find where roi is in image)
        #convert frame to hsv
        hsv= cv2.cvtColor(frame,cv2.COLOR_BGR2HSV);
        mask= cv2.calcBackProject([hsv],[0,1],roi_hist,[0,180,0,256],1) #scale =1
        #mask is the part of roi that is on the image

        #filter mask more
        kernel= cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5));
        mask= cv2.filter2D(mask,-1,kernel);
        #_,mask= cv2.threshold(mask,150,255,cv2.THRESH_BINARY)
        ret, track_window=cv2.CamShift(mask,track_window,term_criteria)
        
         #draw the rectangle found by camshift
        pts = cv2.boxPoints(ret)
        pts = np.int0(pts)
        cv2.polylines(frame,[pts],True, [255,0,0], 2)
        cv2.polylines(mask,[pts],True, [255,0,0], 2)

        cv2.imshow('mask',mask);

    cv2.imshow('frame',frame)

    k= cv2.waitKey(30) &0xff

    if (k==32): # pause the video
        pause= True
    if(k==27):
        break