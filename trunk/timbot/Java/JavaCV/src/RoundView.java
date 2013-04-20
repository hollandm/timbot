import static com.googlecode.javacv.cpp.opencv_highgui.cvSaveImage;

import com.googlecode.javacv.FrameGrabber.Exception;
import com.googlecode.javacv.cpp.opencv_core.IplImage;
import com.googlecode.javacv.cpp.opencv_highgui.CvCapture;
import com.googlecode.javacv.OpenCVFrameGrabber;


public class RoundView {

	public static void main(String[] args) throws Exception {


		
		IplImage[] img = new IplImage[11];
//		for (int i = 1; i < 5; ++i) {
			OpenCVFrameGrabber cam = new OpenCVFrameGrabber(1);
			cam.start();
			long t0 = System.currentTimeMillis();
			img[1] = cam.grab();
			System.out.println(System.currentTimeMillis() - t0);
			cam.stop();
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
