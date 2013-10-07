package snippet;

import com.googlecode.javacv.OpenCVFrameGrabber;

import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

import static com.googlecode.javacv.cpp.opencv_core.cvCreateImage;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSize;
import static com.googlecode.javacv.cpp.opencv_core.cvInRangeS;
import static com.googlecode.javacv.cpp.opencv_core.cvScalar;
import static com.googlecode.javacv.cpp.opencv_highgui.*;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_MEDIAN;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvSmooth;

public class CaptureImage { 
	private static void captureFrame() { 
		// 0-default camera, 1 - next...so on final 
		OpenCVFrameGrabber grabber = new OpenCVFrameGrabber(1);
		try { 
			grabber.start();
			
			
			for (int i = 0; i < 50; i++) {
			
				IplImage img = grabber.grab();
				if (img != null) {
					
					cvSaveImage("capture"+i+".jpg", img);
				} 
				
				
				IplImage imgThreshold = cvCreateImage(cvGetSize(img), 8, 1);
		        //apply thresholding
				CvScalar min = cvScalar(100, 100, 150, 0);//BGR-A
			    CvScalar max= cvScalar(150, 150, 255, 0);//BGR-A
		        cvInRangeS(img, min, max, imgThreshold);
		        
		        //smooth filter- median
		        cvSmooth(imgThreshold, imgThreshold, CV_MEDIAN, 13);
		        //save
		        cvSaveImage("threshold"+i+".jpg", imgThreshold);
		    	
			}
			System.out.println("DONE");
			System.exit(-1);
		} catch (Exception e) { 
			e.printStackTrace();
		} 
		
		
	} 

	public static void main(String[] args) { 
		captureFrame();
	} 
}