import numpy as np
import cv2

class data:
    x = 0
    y = 0


    def on_mouse(self, event, x, y, flags, params):
        self.x = x
        self.y = y

name = "Find the Bucket"
cap = cv2.VideoCapture(0)
mouseCoords = data()
n = 0
showColor = False
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

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

    # Display the resulting frame
    if showColor:
        cv2.imshow('frame',frame)
    else:
        cv2.imshow('frame',dst)
    cv2.setMouseCallback('frame',mouseCoords.on_mouse,0)

    if cv2.waitKey(1) and 0xFF == ord('q'):
        break
    elif cv2.waitKey(1) and 0xFF == ord('t'):
        showColor = not showColor


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()