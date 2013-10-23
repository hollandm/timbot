// Example : grab and write a video file
// usage: prog <output_video>

// Author : Toby Breckon, toby.breckon@cranfield.ac.uk

// Copyright (c) 2010 School of Engineering, Cranfield University
// License : LGPL - http://www.gnu.org/licenses/lgpl.html

#include <cv.h>   	// open cv general include file
#include <highgui.h>	// open cv GUI include file
#include <iostream>	// standard C++ I/O

using namespace cv; // OpenCV API is in the C++ "cv" namespace

int main( int argc, char** argv )
{

	Mat img;  // image object 

	// check that command line arguments are provided

	if( argc == 2 )
	{	

		// here we will use a connected camera as the 
		// originating source for our video file

		//VideoCapture cap(0);  // video capture object
		VideoCapture cap("VID_20130523_170506.m4v");

		if(!cap.isOpened()){              
			std::cout << "error: could not grab a frame" << std::endl;
			exit(0);
		}  
		cap >> img; // retrieve the captured frame as an image

		// set up video writer object (using properties of camera capture source)
		// N.B. we can use "CV_FOURCC('D','I','V','X')" specify an MPEG-4 encoded video
		// just -1 to call up a dialogue box (under MS Windows)	

		VideoWriter videoOutput(argv[1], CV_FOURCC('D','I','V','X') /*-1*/, 25, img.size(), true);
		if(!videoOutput.isOpened()){              
			std::cout << "error: could not open video file" << std::endl;
			exit(0);
		}  

		// loop and store up to N frames

		int nFrames = 500; // 500 frames @ 25 fps = 20 seconds of video

		std::cout << "\nStarting video capture ........" << std::flush; // signal start to user

		for (int i=0;i<nFrames;i++){

			// retreive frame and write to video writer

			cap >> img; // retrieve the captured frame as an image

			//cvtColor(img, img, CV_BGR2GRAY);
			GaussianBlur(img, img, Size(7,7), 1.5, 1.5);
			//Canny(img, img, 0, 30, 3);


			videoOutput << img; // send to video writer object		
		}

		std::cout << " finshed" << std::endl; // signal end to user

		// the camera will be deinitialized automatically in VideoCapture destructor
		// the video file will be deinitialized automatically in VideoWriter destructor	

		// all OK : main returns 0

		return 0;
	}

	// not OK : main returns -1

	return -1;
}

