__author__ = 'matt'


import cv

#g_capture = cv.CreateFileCapture('somevideo.avi')

cv.NamedWindow("w1", cv.CV_WINDOW_AUTOSIZE)
#g_capture = cv.CreateCameraCapture(0)

#g_capture = cv.CreateFileCapture('testDex.avi')
g_capture = cv.CreateFileCapture('VID_20130523_170506.m4v')

while True:
    img=cv.QueryFrame(g_capture)

    cv.ShowImage("w1", img)
    c = cv.WaitKey(10)
