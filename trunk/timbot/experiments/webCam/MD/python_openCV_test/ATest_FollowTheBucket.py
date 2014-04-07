import numpy as np
import cv2

import sys
try:
    sys.path.insert(0, "../../../../prototypeCode/hardwareInterfaces/")
    from animaticsMotors import motorController
    print "Successfully Imported motor controllers."
except ImportError:
    print "Could not import components, terminating program"
    sys.exit()


class data:

    def __init__(self):
        return 

    x = 0
    y = 0
    showColor = False
    nextCommand = 0

    STOP = 0
    LEFT = 1
    RIGHT = 2
    FORWARD = 3


    ## On mouse click, update whatever needs updating.
    def on_mouse(self, event, x, y, flags, params):
        self.x = x
        self.y = y
        if event == cv2.EVENT_LBUTTONDOWN:
            self.showColor = not self.showColor

name = "Find the Bucket"
cap = cv2.VideoCapture(0)
mouseCoords = data()
motors = motorController("/dev/ttyUSB0")
n = 0
lost = 0
while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    cv2.setMouseCallback('frame', mouseCoords.on_mouse, 0)
    # Our operations on the frame come here
    BEACON_MIN = np.array([0, 25, 150], np.uint8)
    BEACON_MAX = np.array([75, 125, 255], np.uint8)
    n += 1
    j = n % 16
    n %= 48
    # if 0 == n:
    #     showColor = not showColor
    ChangeCommand = n % 4
    speed = motorController.SPEED_SLOW
    if 0 == ChangeCommand:
        if mouseCoords.nextCommand == data.LEFT:
            motors.driveLeft(-1*speed)
            motors.driveRight(-1*speed)
        elif mouseCoords.nextCommand == data.RIGHT:
            motors.driveLeft(speed)
            motors.driveRight(speed)
        elif mouseCoords.nextCommand == data.FORWARD:
            motors.driveLeft(speed)
            motors.driveRight(-1*speed)
        else:   # STOP!
            motors.stopLeft()
            motors.stopRight()

    if 0 == j:
        if 0 < mouseCoords.x and 480 > mouseCoords.x and 0 < mouseCoords.y and 640 > mouseCoords.y:
            print "pixel[" + str(mouseCoords.x) + "," + str(mouseCoords.y) + "]:", frame[mouseCoords.x, mouseCoords.y]

    dst = cv2.inRange(frame, BEACON_MIN, BEACON_MAX)
    detector = cv2.SimpleBlobDetector()
    blobs = detector.detect(dst)
    if len(blobs) > 1:
        print "Multiple blobs found."
        lost += 1
        mouseCoords.nextCommand = data.STOP
    elif len(blobs) == 0:
        #no blob found
        lost += 1
    elif len(blobs) == 1:
        lost = 0
        x = blobs[0].pt[0]
        #X coords range from 0 to 640.
        #if the blob is centered between 300 and 380, we're fine.
        #Otherwise, we should turn.
        if x < 280:
            print "LEFT"
            mouseCoords.nextCommand = data.LEFT
            #TODO Turn left
        elif x > 360:
            print "RIGHT"
            #TODO Turn right
            mouseCoords.nextCommand = data.RIGHT
        else:
            print "GO GO GO"
            mouseCoords.nextCommand = data.FORWARD
            #TODO Drive straight.

    #If we've been lost for a while, stop.
    if lost > 35:
        mouseCoords.nextCommand = data.STOP

        #print "Blob found at (" + str(blobs[0].pt[0]) +"," + str(blobs[0].pt[1]) +")."


    # Display the resulting frame
    if mouseCoords.showColor:
        cv2.imshow('frame', frame)
    else:
        cv2.imshow('frame', dst)


    if cv2.waitKey(1) and 0xFF == ord('q'):
        break


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()