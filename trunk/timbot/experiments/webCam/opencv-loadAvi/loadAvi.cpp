#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include </usr/include/opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
	IplImage *frame;
	int key = 'a';
	/* supply the AVI file to play */
	if(argc<2){
		printf("Usage: main <video-file-name>.avi\n\7");
		exit(0);
	}

	/* load the AVI file */
	CvCapture *capture = cvCaptureFromAVI( argv[1] );
	/* always check */
	if( !capture ) return 1;

	/* get fps, needed to set the delay */
	int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
	/* display video */
	cvNamedWindow( "video", 0 );
	while( key != 'q' ) {

		/* get a frame */
		frame = cvQueryFrame( capture );
		/* always check */

		if( !frame ) break;
		
		/* process frame */
		

		/* display frame */
		cvShowImage( "video", frame );
		/* quit if user press 'q' */
		cvWaitKey( 1000 / fps );
	}

	/* free memory */
	cvReleaseCapture( &capture );
	cvDestroyWindow( "video" );
	return 0;
}
