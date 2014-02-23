#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
	CvCapture *capture = cvCaptureFromAVI("testDex.avi");
	if(!capture)
	{   
		printf("!!! cvCaptureFromAVI failed (file not found?)\n");
		return -1; 
	}   

	int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	printf("* FPS: %d\n", fps);

	cvNamedWindow("display_video", CV_WINDOW_AUTOSIZE);

	IplImage* frame = NULL;
	char key = 0;

	while (key != 'q')
	{   
	printf("test1\n");
		frame = cvQueryFrame(capture);
		if (!frame)
		{   
			printf("!!! cvQueryFrame failed: no frame\n");
			break;
		}

	printf("test2\n");
		cvShowImage("display_video", frame);
printf("test3\n");

		key = cvWaitKey(1000 / fps);
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("display_video");

	return 0;
}
