
import static com.googlecode.javacv.cpp.opencv_core.cvInRangeS;
import static com.googlecode.javacv.cpp.opencv_core.cvScalar;
import static com.googlecode.javacv.cpp.opencv_highgui.cvSaveImage;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateImage;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSize;
import static com.googlecode.javacv.cpp.opencv_core.cvGet2D;
import static com.googlecode.javacv.cpp.opencv_core.cvSet2D;
import static com.googlecode.javacv.cpp.opencv_core.cvRectangle;
import static com.googlecode.javacv.cpp.opencv_core.cvPoint;
import java.nio.IntBuffer;

import com.googlecode.javacv.FrameGrabber;
import com.googlecode.javacv.FrameGrabber.Exception;
import com.googlecode.javacv.VideoInputFrameGrabber;
import com.googlecode.javacv.cpp.opencv_core.CvPoint;
import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.IplImage;
import com.googlecode.javacv.cpp.opencv_highgui.CvCapture;
import com.googlecode.javacv.OpenCVFrameGrabber;


public class multiCameraTest {

//	Green
//	static CvScalar min = cvScalar(0, 50, 0, 0);//BGR-A
//    static CvScalar max= cvScalar(50, 200, 50, 0);//BGR-A

//	Red
	static CvScalar min = cvScalar(0, 0, 100, 0);//BGR-A
    static CvScalar max= cvScalar(50, 50, 200, 0);//BGR-A
    public static final int GRID_SIZE = 10; // size of the grid for searching for a color
    public static final int FOV = 90;
	
	public static void main(String[] args) throws Exception {


		String[] cameras = VideoInputFrameGrabber.getDeviceDescriptions();
		System.out.println("Cameras detected:");
		for(String string: cameras){
			System.out.println(string);
		}
		int avgX[] = {0,0,0,0,0,0};
		IplImage[] img = new IplImage[11];
		IplImage[] thr = new IplImage[11];
//		for (int i = 1; i < 5; ++i) {
			//OpenCVFrameGrabber[] cams = {new OpenCVFrameGrabber(0),new OpenCVFrameGrabber(1),new OpenCVFrameGrabber(2),new OpenCVFrameGrabber(3)};
		VideoInputFrameGrabber cam1 = new VideoInputFrameGrabber(1);
		cam1.start();
		System.out.println("Camera 1 loaded.");
		
		VideoInputFrameGrabber cam2 = new VideoInputFrameGrabber(2);	
		cam2.start();
		System.out.println("Camera 2 loaded.");
		
		VideoInputFrameGrabber cam3 = new VideoInputFrameGrabber(3);	
		cam3.start();
		System.out.println("Camera 3 loaded.");
		
		VideoInputFrameGrabber cam4 = new VideoInputFrameGrabber(4);	
		cam4.start();
		System.out.println("Camera 4 loaded.");
		
		
			long t0 = System.currentTimeMillis();
			img[1] = cam1.grab();
			img[2] = cam2.grab();
			img[3] = cam3.grab();
			img[4] = cam4.grab();
			
			//TODO CHANGE The condition to 5
			for (int i = 1; i < 5; i++) {
				thr[i] = cvCreateImage(cvGetSize(img[i]),8,1);
				cvInRangeS(img[i], min, max, thr[i]);
				
				int avgPix = 0;
				int numPix = 0;
						
				//Scanning for colors
				for (int r = 0; r < thr[i].height(); r+=GRID_SIZE) {
					for (int c = r % GRID_SIZE; c < thr[i].width(); c+=GRID_SIZE) {
						CvScalar p = cvGet2D(thr[i],r,c);
						if (p.blue() == 255) {	//all colors should be 255 in this case
							++numPix;
							avgPix += c;
						}
//						System.out.println("b: "+p.blue() + " g: " + p.green() + " r: " + p.red());
						
					}
				}
				
				//get real average value
				avgPix = numPix ==0 ? avgPix : avgPix / numPix;
				avgX[i] = avgPix;
				
				double angle = ((double) avgPix / (double) img[i].width())*FOV;
				
				System.out.println("Avg Position is " + avgPix );
				System.out.println("Esitmated Angle is " + angle );
				
			}
			
			System.out.println(System.currentTimeMillis() - t0);

			
			
			// my path
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+".jpg", img[1]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+2+".jpg", img[2]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+3+".jpg", img[3]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+4+".jpg", img[4]);
//			
			
			// draw a line on the original image where we think the avg is
			CvScalar linePix = new CvScalar();
			linePix.setVal(0, 0);
			linePix.setVal(1, 200);
			linePix.setVal(2, 0);
			CvPoint topPoint = cvPoint(avgX[1],0);
			CvPoint botPoint = cvPoint(avgX[1], thr[1].height() -1);
			
			
			cvRectangle(img[1],topPoint,botPoint,linePix,10,8,0);
			//cvRectangle(thr[1],topPoint,botPoint,linePix,10,8,0);
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+".jpg", img[1]);
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+"t.jpg", thr[1]);
			//end: drawing lines
			
			
			
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+"t.jpg", thr[1]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+2+"t.jpg", thr[2]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+3+"t.jpg", thr[3]);
//			cvSaveImage("C:\\robots\\Webcam Pictures\\"+4+"t.jpg", thr[4]);
			

			System.out.println("After Saving "+(System.currentTimeMillis() - t0));
			
			cam1.stop();
			cam2.stop();
			cam3.stop();
			cam4.stop();

			cam1.release();
			cam2.release();
			cam3.release();
			cam4.release();

//		}
		
//		long t0 = System.currentTimeMillis();
//		IplImage[] img = new IplImage[11];
//		for (int i = 1; i < 5; ++i) {
//			OpenCVFrameGrabber cam = new OpenCVFrameGrabber(i);
//			cam.start();
//
//			img[i] = cam.grab();
//			if (img[i] != null) {
//
//				cvSaveImage("capture"+i+".jpg", img[i]);
//			} 
//			cam.stop();
//		}
//		System.out.println(System.currentTimeMillis() - t0);

		System.out.println("Done");
		System.exit(0);
	}

}
