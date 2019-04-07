import numpy as np
import cv2 
#load two cascades
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')

cap = cv2.VideoCapture(0)

while True:
    ret, frame= cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5) #detect all faces in gray
    for (x,y,w,h) in faces: # for all faces
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2) #blue rectangle with width of 0
        roi_gray = gray[y:y+h, x:x+w] #location of faces
        roi_color = frame[y:y+h, x:x+w] #location of faces on color
       # eyes = eye_cascade.detectMultiScale(roi_gray)
       # for (ex,ey,ew,eh) in eyes:
        #    cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2) #draw green
    cv2.imshow('frame',frame)
    k=cv2.waitKey(30) & 0xff
    if k==27:
        break

cap.release()    
cv2.destroyAllWindows()

