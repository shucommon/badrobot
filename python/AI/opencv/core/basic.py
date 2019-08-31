import numpy as np
import cv2 as cv

img = cv.imread('img.png')

pt = (0,0)

# get a pixel BGR
px = img[pt]
print(type(px))
print(px)

# get only blue channel
blue = img[pt, 0]
print(blue)

b,g,r = img[pt]
print(type(b))
print(b, g, r)

# modify a pixel
img[pt] = [255,255,255]
print(img[pt])

# Better pixel accessing and editing method:
# accessing RED value
print(img.item(10,10,2))
# modifying RED value
img.itemset((10,10,2),100)
print(img.item(10,10,2))
