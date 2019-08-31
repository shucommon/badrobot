import numpy as np
import cv2 as cv

cap = cv.VideoCapture(0)
# Define the codec and create VideoWriter object
# fourcc = cv.VideoWriter_fourcc(*'MJPG')
# out = cv.VideoWriter('output.mp4', fourcc, 20.0, (1280,  720), isColor=True)
# fourcc = cv.VideoWriter_fourcc(*'X264')
# out = cv.VideoWriter('output.mkv', fourcc, 20.0, (1280,  720), isColor=True)
fourcc = cv.VideoWriter_fourcc(*'DIVX')
out = cv.VideoWriter('output.avi', fourcc, 20.0, (1280,  720), isColor=True)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    # frame = cv.flip(frame, 0)
    # write the flipped frame
    out.write(frame)
    cv.imshow('frame', frame)
    if cv.waitKey(1) == ord('q'):
        break
# Release everything if job is finished
cap.release()
out.release()
cv.destroyAllWindows()
