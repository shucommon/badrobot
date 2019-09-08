import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

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
print('accessing RED value:')
print('img.item(10,10,2)')
print(img.item(10,10,2))
print('modifying RED value:')
print('img.itemset((10,10,2),100)')
img.itemset((10,10,2),100)
print(img.item(10,10,2))

# Image Properties
# The shape of an image is accessed by img.shape.
print('img.shape returns a tuple of number of rows, columns, and channels (if image is color):')
print('img.shape')
print(img.shape)

print('Total number of pixels is accessed by img.size:')
print(img.size)

print('Image datatype is obtained by `img.dtype`:')
print(img.dtype)


# Image ROI
# ROI is again obtained using Numpy indexing.
# Here I am selecting the ball and copying it to another region in the image:
# [row1:row2, col1:col2]
ball = img[160:240, 60:130]
img[160:240, 150:220] = ball

# Splitting and Merging Image Channels
b,g,r = cv.split(img)
img = cv.merge((b,g,r))

# or
# b = img[:,:,0]
# print('Suppose you want to set all the red pixels to zero, you do not need to split the channels first. Numpy indexing is faster:')
# img[:,:,2] = 0

cv.imshow('img', img)
cv.imshow('img1', b)
cv.imshow('img2', g)
cv.imshow('img3', r)
cv.waitKey(0)

print('Making Borders for Images (Padding)')
# cv.copyMakeBorder()
'''
src - input image
top, bottom, left, right - border width in number of pixels in corresponding directions
borderType - Flag defining what kind of border to be added. It can be following types:
cv.BORDER_CONSTANT - Adds a constant colored border. The value should be given as next argument.
cv.BORDER_REFLECT - Border will be mirror reflection of the border elements, like this : fedcba|abcdefgh|hgfedcb
cv.BORDER_REFLECT_101 or cv.BORDER_DEFAULT - Same as above, but with a slight change, like this : gfedcb|abcdefgh|gfedcba
cv.BORDER_REPLICATE - Last element is replicated throughout, like this: aaaaaa|abcdefgh|hhhhhhh
cv.BORDER_WRAP - Can't explain, it will look like this : cdefgh|abcdefgh|abcdefg
value - Color of border if border type is cv.BORDER_CONSTANT
'''

BLUE = [255,0,0]
#img1 = cv.imread('opencv-logo.png')
img1 = img
replicate = cv.copyMakeBorder(img1,10,10,10,10,cv.BORDER_REPLICATE)
reflect = cv.copyMakeBorder(img1,10,10,10,10,cv.BORDER_REFLECT)
reflect101 = cv.copyMakeBorder(img1,10,10,10,10,cv.BORDER_REFLECT_101)
wrap = cv.copyMakeBorder(img1,10,10,10,10,cv.BORDER_WRAP)
constant= cv.copyMakeBorder(img1,10,10,10,10,cv.BORDER_CONSTANT,value=BLUE)
plt.subplot(231),plt.imshow(img1,'gray'),plt.title('ORIGINAL')
plt.subplot(232),plt.imshow(replicate,'gray'),plt.title('REPLICATE')
plt.subplot(233),plt.imshow(reflect,'gray'),plt.title('REFLECT')
plt.subplot(234),plt.imshow(reflect101,'gray'),plt.title('REFLECT_101')
plt.subplot(235),plt.imshow(wrap,'gray'),plt.title('WRAP')
plt.subplot(236),plt.imshow(constant,'gray'),plt.title('CONSTANT')
plt.show()


