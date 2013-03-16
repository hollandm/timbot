package snippet;
//static imports
import static com.googlecode.javacv.cpp.opencv_core.*;
import static com.googlecode.javacv.cpp.opencv_highgui.*;
import static com.googlecode.javacv.cpp.opencv_imgproc.*;
//non-static imports
import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

public class ColorDetect {
    //color range of red like color
	static CvScalar min = cvScalar(0, 0, 130, 0);//BGR-A
    static CvScalar max= cvScalar(180, 110, 255, 0);//BGR-A

    public static void main(String[] args) {
        //read image
        IplImage orgImg = cvLoadImage("E:/Robotics/SVN/Java/JavaCV/capture.jpg");
        //create binary image of original size
        IplImage imgThreshold = cvCreateImage(cvGetSize(orgImg), 8, 1);
        //apply thresholding
        cvInRangeS(orgImg, min, max, imgThreshold);
        
        //smooth filter- median
        cvSmooth(imgThreshold, imgThreshold, CV_MEDIAN, 13);
        //save
        cvSaveImage("threshold.jpg", imgThreshold);
    }
}