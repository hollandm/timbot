package snippet;
import static com.googlecode.javacpp.Loader.sizeof;
import static com.googlecode.javacv.cpp.opencv_core.CV_FILLED;
import static com.googlecode.javacv.cpp.opencv_core.CV_RGB;
import static com.googlecode.javacv.cpp.opencv_core.IPL_DEPTH_8U;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateImage;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateMemStorage;
import static com.googlecode.javacv.cpp.opencv_core.cvDrawContours;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSize;
import static com.googlecode.javacv.cpp.opencv_core.cvPoint;
import static com.googlecode.javacv.cpp.opencv_highgui.cvLoadImage;
import static com.googlecode.javacv.cpp.opencv_highgui.cvSaveImage;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_BGR2GRAY;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_CHAIN_APPROX_SIMPLE;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_RETR_CCOMP;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_THRESH_BINARY;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvCvtColor;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvFindContours;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvThreshold;

import java.awt.Color;
import java.util.Random;

import com.googlecode.javacv.cpp.opencv_core.CvContour;
import com.googlecode.javacv.cpp.opencv_core.CvMemStorage;
import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.CvSeq;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

/**
 * A demo for blob extraction using only JavaCV / OpenCV
 * @see http://stackoverflow.com/questions/4641817/blob-extraction-in-opencv
 * @see http://voices.yahoo.com/connected-components-using-opencv-5462975.html?cat=15
 * @see http://opencv.willowgarage.com/documentation/cpp/structural_analysis_and_shape_descriptors.html#cv-findcontours
 * @author happyburnout
 */

public class JavaCVBlobDemo {

    static String sourcePath = "E:/Robotics/SVN/Java/JavaCV/capture.jpg";
    static String targetPath = "E:/Robotics/SVN/Java/JavaCV/detect.jpg";

    public static void main (String args[]){
        IplImage image = cvLoadImage(sourcePath);
        IplImage grayImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
        cvCvtColor(image, grayImage, CV_BGR2GRAY);

        CvMemStorage mem;
        CvSeq contours = new CvSeq();
        CvSeq ptr = new CvSeq();
        cvThreshold(grayImage, grayImage, 150, 255, CV_THRESH_BINARY);
        mem = cvCreateMemStorage(0);

        cvFindContours(grayImage, mem, contours, sizeof(CvContour.class) , CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

        Random rand = new Random();
        for (ptr = contours; ptr != null; ptr = ptr.h_next()) {
            Color randomColor = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
            CvScalar color = CV_RGB( randomColor.getRed(), randomColor.getGreen(), randomColor.getBlue());
            cvDrawContours(image, ptr, color, CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));
        }
        cvSaveImage(targetPath, image);
    }

}