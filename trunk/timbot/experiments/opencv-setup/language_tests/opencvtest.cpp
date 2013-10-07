#include "opencvtest.hpp"
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{

    Mat img = imread("/home/matt/Desktop/001481663.jpeg",CV_LOAD_IMAGE_COLOR);
    imshow("opencvtest",img);
    waitKey(0);

    return 0;
}
