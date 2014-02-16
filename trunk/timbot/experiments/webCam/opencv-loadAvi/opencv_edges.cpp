#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	//VideoCapture cap("VID_20130523_170506.m4v"); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
		return -1;

	int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
			(int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));


	VideoWriter outputVideo;                                        // Open the output

	outputVideo.open("edgesVid.avi", CV_FOURCC('D','I','V','X'), 10, S, true);
	if (!outputVideo.isOpened())
	{
		cout  << "Could not open the output video for write: " << endl;
		return -1;
	}

	Mat edges;
	//namedWindow("edges",1);
	for(;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		if (frame.empty()) break;

		
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);

		outputVideo.write(edges);
		//outputVideo << edges;
		
		imshow("edges", edges);
		if(waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
