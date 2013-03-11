package snippet;

import java.nio.ByteBuffer;

import com.googlecode.javacv.FrameGrabber;
import com.googlecode.javacv.FrameGrabber.Exception;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

public class Snippet {
	public static void main(String[] args) {
		FrameGrabber grabber;
		try {
			System.out.println("Test1");
			grabber = FrameGrabber.createDefault(0);

			System.out.println("Test2");
			grabber.start();

			System.out.println("Test3");
			grabber.grab();
			IplImage grabbedImage = grabber.grab();
			

			System.out.println("Test4");
			int width  = grabbedImage.width();
			int height = grabbedImage.height();

//			grabbedImage.
			
			System.out.println(width + " " + height);


			System.out.println("Test5");
//			grabber.stop();
			
//			grabber.release();
			grabber.stop();
			
			
			//K i have an image now so do something with it
//			grabbedImage.asByteBuffer();
			
			
//			Bitmap bitmapImage;
			
//			ByteBuffer buffer = ByteBuffer.allocate(bitmapImage.getWidth()*bitmapImage.getHeight()*4);
//	        bitmapImage.copyPixelsToBuffer(buffer);
//	        IplImage iplImage = IplImage.create(bitmapImage.getWidth(), bitmapImage.getHeight(), 8, 3); // depth 8-bit and 3 channels
//	        iplImage.imageData(buffer);
			
		} catch (Exception e) {
//			e.printStackTrace();
		}
	}
}

