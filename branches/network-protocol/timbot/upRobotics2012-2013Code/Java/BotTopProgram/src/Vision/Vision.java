package Vision;

import com.googlecode.javacv.FrameGrabber.Exception;

public class Vision {

	
	
	//The index of the last webcam the beacon was found in
	int lastFound = -1;
	
	Eye[] eyes;
	
	public Vision() {
		
		eyes = new Eye[4];
		for (int i = 0; i < 4; ++i) {
			eyes[i] = new Eye(i+1);
		}
	}
	
	
	public double scanAll() {
		double angle = -1;
		
		for (int i = 0; i < 4; ++i) {
			
			try {
				angle = eyes[i].findBeconAngle();
				
				if (angle >= 0) {
					lastFound = i;
					System.out.println("Found");
					break;
				} else {
					System.out.println("Failed");
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
		
		//TODO: format angle
		return angle;
		
	}
	
	public static void main(String[] args) {
		
		Vision v = new Vision();
		System.out.println(v.scanAll() + " " + v.lastFound);
		
		for (int i = 0; i < 4; ++i) {
			v.eyes[i].close();
		}
		
	}
	
}
