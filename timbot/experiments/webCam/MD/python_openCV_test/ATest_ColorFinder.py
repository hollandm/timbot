import numpy as np
import cv2

class data:
    x = 0
    y = 0
    showColor = False


    ## On mouse click, update whatever needs updating.
    def on_mouse(self, event, x, y, flags, params):
        self.x = x
        self.y = y
        if event == cv2.EVENT_LBUTTONDOWN:
            self.showColor = not self.showColor

name = "Find the Bucket"
cap = cv2.VideoCapture(0)
mouseCoords = data()
n = 0
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    cv2.setMouseCallback('frame',mouseCoords.on_mouse,0)
    # Our operations on the frame come here
    BEACON_MIN = np.array([0, 25, 150], np.uint8)
    BEACON_MAX = np.array([75, 125, 255], np.uint8)
    n += 1
    j = n % 16
    n %= 48
    #if 0 == n:
        #showColor = not showColor

    if 0 == j:
        if 0 < mouseCoords.x and 480 > mouseCoords.x and 0 < mouseCoords.y and 640 > mouseCoords.y:
            print "pixel[" + str(mouseCoords.x) + "," + str(mouseCoords.y) + "]:", frame[mouseCoords.x,mouseCoords.y]

    dst = cv2.inRange(frame, BEACON_MIN, BEACON_MAX)
    detector = cv2.SimpleBlobDetector()
    blobs = detector.detect(dst)
    if len(blobs) > 1:
        print "Multiple blobs found."

    if len(blobs) == 1:
        print "Blob found at (" + str(blobs[0].pt[0]) +"," + str(blobs[0].pt[1]) +")."

    # Display the resulting frame
    if mouseCoords.showColor:
        cv2.imshow('frame',frame)
    else:
        cv2.imshow('frame',dst)


    if cv2.waitKey(1) and 0xFF == ord('q'):
        break


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()