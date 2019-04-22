#helped in detecting hough circles on template sheet


cropped = cv2.cvtColor(cropped,cv2.COLOR_BGR2GRAY)
img= cv2.GaussianBlur(cropped,(7,7),0) 

#circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=14,maxRadius=14)



circles = cv2.HoughCircles(img,cv2.HOUGH_GRADIENT,1,12,param1=10,param2=10,minRadius=HOUGH_RADIUS,maxRadius=HOUGH_RADIUS)

circles = np.uint16(np.around(circles))
circles=sorted(circles[0,:],key=operator.itemgetter(1,0),reverse=False)
#cv2.circle(img, center, radius, color, thickness=1, lineType=8, shift=0) 
student_count=0;
choice_count=0;
count=0;
fa= open("answers.txt","r")
fs=  open("student_2.txt","r")
lines=fs.readlines()
#for i in circles:
    # draw the outer circle
 #   if(i[0]>52 and i[0]<450 and i[1]<1500): #circles for student number
  #      cv2.circle(cropped,(i[0],i[1]),i[2],(0,255,0),2)
        
        #fs.write(str(i[0])+" "+str(i[1])+"\n")
        #studentNumber(cropped,i,student_count) 
      #draw the center of the circle
   #     cv2.circle(cropped,(i[0],i[1]),2,(0,0,255),3)
    #    count+=1;

    #if(count==4):
     #   break
   # if((i[0]>500 and i[0]<800 or i[0]>850) and i[1]<1800):
        #studentNumber(cropped,i,student_count) 
      #  fa.write(str(i[0])+" "+str(i[1])+"\n")
        
        #print(cropped[i[1]][i[0]])
        #cv2.circle(cropped,(i[0],i[1]),i[2],(0,255,0),2)
    ##draw the center of the circle
      #  cv2.circle(cropped,(i[0],i[1]),2,(0,0,255),3) 
        #count+=1;