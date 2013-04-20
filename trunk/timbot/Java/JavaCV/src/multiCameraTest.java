package snippet;

import static com.googlecode.javacv.cpp.opencv_core.cvInRangeS;
import static com.googlecode.javacv.cpp.opencv_core.cvScalar;
import static com.googlecode.javacv.cpp.opencv_highgui.cvSaveImage;

import com.googlecode.javacv.FrameGrabber;
import com.googlecode.javacv.FrameGrabber.Exception;
import com.googlecode.javacv.VideoInputFrameGrabber;
import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.IplImage;
import com.googlecode.javacv.cpp.opencv_highgui.CvCapture;
import com.googlecode.javacv.OpenCVFrameGrabber;


public class multiCameraTest {

	static CvScalar min = cvScalar(100, 100, 200, 0);//BGR-A
    static CvScalar max= cvScalar(200, 200, 255, 0);//BGR-A
	
	public static void main(String[] args) throws Exception {


		String[] cameras = VideoInputFrameGrabber.getDeviceDescriptions();
		System.out.println("Cameras detected:");
		for(String string: cameras){
			System.out.println(string);
		}

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
			
			//for (int i = 1; i < 5; i++) {
			//	cvInRangeS(img[1], min, max, thr[1]);
			//}
			
			System.out.println(System.currentTimeMillis() - t0);

			// my path
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+".jpg", img[1]);
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+2+".jpg", img[2]);
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+3+".jpg", img[3]);
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+4+".jpg", img[4]);
			
			//cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+"t.jpg", thr[1]);
			//cvSaveImage("C:\\robots\\Webcam Pictures\\"+2+"t.jpg", thr[2]);
			//cvSaveImage("C:\\robots\\Webcam Pictures\\"+3+"t.jpg", thr[3]);
			
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
