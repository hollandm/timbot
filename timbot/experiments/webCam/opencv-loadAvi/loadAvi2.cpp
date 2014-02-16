#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(){
	cv::Mat frame;
	//cv::VideoCapture cap("testDex.avi");
	cv::VideoCapture cap(0);

	cout << "test1" << endl;

	if(!cap.isOpened()){
		cout << "Error can't find the file"<<endl;
	}

	cout << "test2" << endl;

	while(1){

		//cap.grab();
		//cap.retrieve(frame);
		cap.read(frame);
		imshow("",frame);

		//if(!cap.read(frame))
		//{
		//	cout << "test3" << endl;
		//	imshow("",frame);
		//	cout << "test4" << endl;
		//}

		cout << "test5" << endl;
		cv::waitKey(33);

	}
	return 0;
}
