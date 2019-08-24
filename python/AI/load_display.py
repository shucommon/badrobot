import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
# opencv in BGR mode, matplot in RGB mode

#name = input('input image name: ')
name = 'lucky.jpeg'
#name = 'img.png'
# cv.IMREAD_COLOR/IMREAD_GRAYSCALE/IMREAD_UNCHANGED 1/0/-1
img = cv.imread(name)
print('height %d' % (img.shape[0]))
print('weidth %d' % (img.shape[1]))
print('channel %d' % (img.shape[2]))

'''
cv.imshow('image',img)
cv.waitKey(0)
#cv.destroyAllWindows()
cv.destroyWindow('image')

#cv.namedWindow('image', cv.WINDOW_AUTOSIZE)
cv.namedWindow('image', cv.WINDOW_NORMAL)
cv.imshow('image',img)
cv.waitKey(0)
cv.destroyAllWindows()

#cv.imwrite('lucky-1.png',img)

#plt.imshow(img, cmap = 'gray', interpolation = 'bicubic')
plt.imshow(img, interpolation = 'bicubic')
plt.xticks([]), plt.yticks([])  # to hide tick values on X and Y axis
plt.show()
'''

# b,g,r = cv.split(img)
# img2 = cv.merge([r,g,b])
# a more usefull way to convert bgr to rgb
# img2 = img[:,:,::-1]
# cv func method
img2 = cv.cvtColor(img, cv.COLOR_BGR2RGB)
plt.subplot(121);plt.imshow(img) # expects distorted color
plt.axis('off')
plt.subplot(122);plt.imshow(img2) # expect true color
plt.axis('off')
plt.show()

cv.namedWindow('bgr image', cv.WINDOW_NORMAL)
cv.namedWindow('rgb image', cv.WINDOW_NORMAL)
cv.imshow('bgr image',img) # expects true color
cv.imshow('rgb image',img2) # expects distorted color
cv.waitKey(0)
cv.destroyAllWindows()

