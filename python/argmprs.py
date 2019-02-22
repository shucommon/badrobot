# import the necessary packages
from imutils.video import VideoStream
from imutils import paths
import itertools
import argparse
import imutils
import time
import cv2

'''
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True, help="input image")
args = vars(ap.parse_args())

img = cv2.imread(args["image"])
#cv2.imshow("hello", img)
#cv2.waitKey()
'''

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-m", "--models", required=True,
        help="path to directory containing neural style transfer models")
args = vars(ap.parse_args())

# grab the paths to all neural style transfer models in our 'models'
# directory, provided all models end with the '.t7' file extension
modelPaths = paths.list_files(args["models"], validExts=(".t7",))
modelPaths = sorted(list(modelPaths))

# generate unique IDs for each of the model paths, then combine the
# two lists together
models = list(zip(range(0, len(modelPaths)), (modelPaths)))

# use the cycle function of itertools that can loop over all model
# paths, and then when the end is reached, restart again
modelIter = itertools.cycle(models)
print modelIter
(modelID, modelPath) = next(modelIter)
print modelID
print modelPath
(modelID, modelPath) = next(modelIter)
print modelID
print modelPath
