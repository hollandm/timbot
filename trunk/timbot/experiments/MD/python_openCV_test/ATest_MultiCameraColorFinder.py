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

######################################################
## This demo requires 2 cameras.
##
######################################################
name = "Find the Bucket"
cam0 = cv2.VideoCapture(0)
cam1 = cv2.VideoCapture(1)
#cam2 = cv2.VideoCapture(2)
settings = data()
BEACON_MIN = np.array([0, 25, 150], np.uint8)
BEACON_MAX = np.array([75, 125, 255], np.uint8)
n = 0
ret = [0,1,2,3]
frame = [0,1,2,3]
dst = [0,1,2,3]
#Default correct camera to 0
correctCamera = 0
while(True):
    # Capture frame-by-frame
    ret[0], frame[0] = cam0.read()
    ret[1], frame[1] = cam1.read()
    #ret[2], frame[2] = cam2.read()
    cv2.setMouseCallback('frame',settings.on_mouse,0)
    imgs = {}
    # Our operations on the frame come here
    n += 1
    j = n % 16
    n %= 48

    #Process the camera input
    dst[0] = cv2.inRange(frame[0], BEACON_MIN, BEACON_MAX)
    count0 = cv2.countNonZero(dst[0])
    imgs[str(count0)] = 0

    dst[1] = cv2.inRange(frame[1], BEACON_MIN, BEACON_MAX)
    count1 = cv2.countNonZero(dst[1])
    imgs[str(count1)] = 1

    #dst[2] = cv2.inRange(frame[2], BEACON_MIN, BEACON_MAX)
    #count2 = cv2.countNonZero(dst[2])
    #imgs[str(count2)] = 2
    count2 = -2 #unused
    imgs[str(count2)] = 2
    count3 = -3 #Unused
    imgs[str(count3)] = 3

    #Determine which camera to use
    guess = max(count0,count1,count2,count3)
    if 0 == n % 16:
        print "Max Orange Pixels: " + str(guess)
    if guess > 500:
        correctCamera = int(imgs[str(guess)])
    else:
        print "Unsure of correct camera."

    if 0 == j:
        if 0 < settings.x and 480 > settings.x and 0 < settings.y and 640 > settings.y:
            print "pixel[" + str(settings.x) + "," + str(settings.y) + "]:", frame[correctCamera][settings.x,settings.y]
    # Label and display the resulting frame
    if settings.showColor:
        cv2.putText(frame[correctCamera],str(correctCamera), (10,50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0))
        cv2.imshow('frame',frame[correctCamera])
    else:
        cv2.putText(dst[correctCamera],str(correctCamera), (10,50), cv2.FONT_HERSHEY_SIMPLEX, 2, (255,255,255))
        cv2.imshow('frame',dst[correctCamera])


    if cv2.waitKey(1) and 0xFF == ord('q'):
        break


# When everything done, release the capture
cam0.release()
cam1.release()
cam2.release()
cv2.destroyAllWindows()