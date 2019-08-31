'''
For cv.getTrackbarPos() function,
first argument is the trackbar name,
second one is the window name to which it is attached,
third argument is the default value,
fourth one is the maximum value
fifth one is the callback function which is executed everytime trackbar value changes.
The callback function always has a default argument which is the trackbar position.
In our case, function does nothing, so we simply pass.
'''
import numpy as np
import cv2 as cv

def nothing(x):
    cv.rectangle(img,(0,0),(40,20),(b,g,r),-1)

# mouse callback function
def draw_circle(event,x,y,flags,param):
    if event == cv.EVENT_LBUTTONDOWN:
        color = (b,g,r)
        cv.circle(img,(x,y),rad,color,-1)

# Create a black image, a window
img = np.zeros((300,512,3), np.uint8)
cv.namedWindow('image')
# create trackbars for color change
cv.createTrackbar('R','image',0,255,nothing)
cv.createTrackbar('G','image',0,255,nothing)
cv.createTrackbar('B','image',0,255,nothing)
cv.createTrackbar('rad','image',0,50,nothing)
cv.setMouseCallback('image',draw_circle)
while(1):
    global r, g, b, rad
    cv.imshow('image',img)
    k = cv.waitKey(1) & 0xFF
    if k == ord('q'):
        break
    elif k == ord('c'):
        cv.rectangle(img,(0,0),(511,299),(0,0,0),-1)
    # get current positions of four trackbars
    r = cv.getTrackbarPos('R','image')
    g = cv.getTrackbarPos('G','image')
    b = cv.getTrackbarPos('B','image')
    rad = cv.getTrackbarPos('rad','image')
    # img[:] = [b,g,r]
cv.destroyAllWindows()

