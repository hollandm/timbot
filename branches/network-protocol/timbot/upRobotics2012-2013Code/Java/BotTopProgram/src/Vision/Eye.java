package Vision;

import static com.googlecode.javacv.cpp.opencv_core.cvCreateImage;
import static com.googlecode.javacv.cpp.opencv_highgui.cvSaveImage;
import static com.googlecode.javacv.cpp.opencv_core.cvGet2D;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSize;
import static com.googlecode.javacv.cpp.opencv_core.cvInRangeS;
import static com.googlecode.javacv.cpp.opencv_core.cvPoint;
import static com.googlecode.javacv.cpp.opencv_core.cvRectangle;
import static com.googlecode.javacv.cpp.opencv_core.cvScalar;

import com.googlecode.javacv.FrameGrabber.Exception;
import com.googlecode.javacv.VideoInputFrameGrabber;
import com.googlecode.javacv.cpp.opencv_core.CvPoint;
import com.googlecode.javacv.cpp.opencv_core.CvScalar;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

public class Eye {

	public static final int FOV = 90;		//Field of view
	public static final int GRID_SIZE = 10; // size of the grid for searching for a color
	
	/**
	 * the minimum number of pixels we have to see to determine
	 * that we have found the beacon and it we are not just getting
	 * a false positive
	 */
	public static final int minPix = 10;	
	
	public static final boolean saveBaseImage = false;
	public static final boolean saveThresholdImage = false;
	public static final boolean saveAngleImage = false;

	static CvScalar scanColorMin = cvScalar(0, 0, 100, 0);//BGR-A
	static CvScalar scanColorMax= cvScalar(50, 50, 200, 0);//BGR-A

	public VideoInputFrameGrabber cam;

	public Eye(int camNum) {


		try {
			cam = new VideoInputFrameGrabber(camNum);
			cam.start();
			
			System.out.println("Camera "+camNum+" loaded.");
		} catch (Exception e) {
			System.err.println("CANT OPEN THE CAMERA, CRAP!");
			System.exit(-1);
		}

	}

	/**
	 * findBeconAngle detects the beacon and returns the angle to the number
	 * the angle will be a number between 0 and 90 0 being at the left most side
	 * returns -1 if the beacon is not seen.
	 * 
	 * @return angle
	 * @throws Exception 
	 */
	public double findBeconAngle() throws Exception {
		double angle;
		
		IplImage img = cam.grab();

		if (saveBaseImage) {
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+cam+".jpg", img);
		}
		
		IplImage thr = cvCreateImage(cvGetSize(img),8,1);
		cvInRangeS(img, scanColorMin, scanColorMax, thr);

		if (saveThresholdImage) {
			cvSaveImage("C:\\robots\\Webcam Pictures\\"+cam+".jpg", thr);
		}
		
		int avgPix = 0;
		int numPix = 0;

		//Scanning for colors
		for (int r = 0; r < thr.height(); r+=GRID_SIZE) {
			for (int c = r % GRID_SIZE; c < thr.width(); c+=GRID_SIZE) {
				CvScalar p = cvGet2D(thr,r,c);
				if (p.blue() == 255) {	//all colors should be 255 in this case
					++numPix;
					avgPix += c;
				}
				//					System.out.println("b: "+p.blue() + " g: " + p.green() + " r: " + p.red());

			}
		}


		if (numPix < 5) {
			return -1;
		}

		//get real average value
		avgPix /= numPix;

		angle = ((double) avgPix / (double) img.width())*FOV;

		System.out.println("Avg Position is " + avgPix );
		System.out.println("Esitmated Angle is " + angle );

		if (saveAngleImage) {
			CvScalar linePix = new CvScalar();
				linePix.setVal(0, 0);
				linePix.setVal(1, 200);
				linePix.setVal(2, 0);
			CvPoint topPoint = cvPoint(avgPix,0);
			CvPoint botPoint = cvPoint(avgPix, thr.height() -1);			
			cvRectangle(img,topPoint,botPoint,linePix,10,8,0);

			cvSaveImage("C:\\robots\\Webcam Pictures\\"+1+"r.jpg", img);
		}

		return angle;

	}
	
	public void close() {
		try {
			cam.stop();
			cam.release();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
}
