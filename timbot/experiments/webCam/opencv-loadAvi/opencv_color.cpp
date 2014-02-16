#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;

static void help()
{
	cout
		<< "------------------------------------------------------------------------------" << endl
		<< "This program shows how to write video files."                                   << endl
		<< "You can extract the R or G or B color channel of the input video."              << endl
		<< "Usage:"                                                                         << endl
		<< "./video-write inputvideoName [ R | G | B] [Y | N]"                              << endl
		<< "------------------------------------------------------------------------------" << endl
		<< endl;
}

int main(int argc, char *argv[])
{
	help();

	int debug = 0;

	if (argc != 4)
	{
		cout << "Not enough parameters" << endl;
		return -1;
	}

	const string source      = "VID_20130523_170506.m4v";//argv[1];           // the source file name
	const bool askOutputType = argv[3][0] =='Y';  // If false it will use the inputs codec type


	cout << "debug print " << ++debug << endl;

	VideoCapture inputVideo(source);              // Open input
	//VideoCapture inputVideo(0);              // Open input

	cout << "debug print " << ++debug << endl;
	if (!inputVideo.isOpened())
	{
		cout  << "Could not open the input video: " << source << endl;
		return -1;
	}

	cout << "debug print " << ++debug << endl;
	string::size_type pAt = source.find_last_of('.');                  // Find extension point
	const string NAME = source.substr(0, pAt) + argv[2][0] + ".avi";   // Form the new name with container
	int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form

	cout << "debug print " << ++debug << endl;
	// Transform from int to char via Bitwise operators
	char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};

	cout << "debug print " << ++debug << endl;
	Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
			(int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

	cout << "debug print " << ++debug << endl;
	VideoWriter outputVideo;                                        // Open the output
	cout << "debug print " << ++debug << endl;
	/*
	if (askOutputType)
		outputVideo.open(NAME, ex=-1, inputVideo.get(CV_CAP_PROP_FPS), S, true);
	else
		outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);
	*/
	int fps =  inputVideo.get(CV_CAP_PROP_FPS);
	cout << "debug print " << ++debug << endl;
	outputVideo.open("colors.avi", 0, fps, S, true);

	cout << "debug print " << ++debug << endl;
	if (!outputVideo.isOpened())
	{
		cout  << "Could not open the output video for write: " << source << endl;
		return -1;
	}

	cout << "debug print " << ++debug << endl;
	cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
		<< " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
	cout << "Input codec type: " << EXT << endl;

	int channel = 2; // Select the channel to save
	switch(argv[2][0])
	{
		case 'R' : channel = 2; break;
		case 'G' : channel = 1; break;
		case 'B' : channel = 0; break;
	}
	Mat src, res;
	vector<Mat> spl;

	cout << "debug print " << ++debug << endl;
	for(;;) //Show the image captured in the window and repeat
	{
		inputVideo >> src;              // read
		if (src.empty()) break;         // check if at end

		cout << "debug print " << ++debug << endl;
		split(src, spl);                // process - extract only the correct channel
		for (int i =0; i < 3; ++i)
			if (i != channel)
				spl[i] = Mat::zeros(S, spl[0].type());

		//cout << "debug print " << ++debug << endl;
		merge(spl, res);

		//cout << "debug print " << ++debug << endl;
		//outputVideo.write(res); //save or
		outputVideo << res;
	}

	cout << "Finished writing" << endl;
	return 0;
}

