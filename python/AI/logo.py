import numpy as np
import cv2 as cv


# Create a black image
img = np.zeros((512,512,3), np.uint8)

# We will write OpenCV on our image in white color
#font = cv.FONT_HERSHEY_SIMPLEX
#cv.putText(img,'OpenCV',(10,500), font, 4,(255,255,255),2,cv.LINE_AA)
# cv.circle(img, centor, r, color, 15)

r = 50
s = 0
e = 300
width = 20

color = (0,0,255)
centor = (256, 200)
ro = 120
cv.ellipse(img, centor,(r, r), ro, s, e, color, width)


color = (0,255,0)
centor = (190, 315)
ro = 0
cv.ellipse(img, centor,(r, r), ro, s, e, color, width)

color = (255,0,0)
centor = (322, 315)
ro = 300
cv.ellipse(img, centor,(r, r), ro, s, e, color, width)

font = cv.FONT_HERSHEY_SIMPLEX
cv.putText(img,'OpenCV',(125,450), font, 2.3, (255,255,255),3,cv.LINE_AA)


cv.imshow('img', img)
cv.waitKey(0)
