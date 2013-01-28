
public class AOutput {

	/**
	 * Extend the bucket by the given distance
	 * @param dst
	 */
	public void acuateArm(float spd) {}			//TODO
	
	/**
	 * Extend the bucket by the given distance 
	 * @param dst
	 */
	public void acuateBucket(float spd) {}		//TODO
	
	
	/**
	 * Extend the arm to the target distance 
	 * @param dst
	 */
	public void targetArm(float dst) {}			//TODO
	
	/**
	 * Extend the bucket to the target distance 
	 * @param dst
	 */
	public void targetBucket(float dst) {}		//TODO
	
	
	/**
	 * Rotate counter clockwise, negative values go clockwise
	 * @param ang: angle in degrees to turn
	 */
	public void rotate(float ang) {}			//TODO
	
	/**
	 * Drive straight
	 * @param speed
	 */
	public void driveStraight(float speed) {
		driveLeft(speed);
		driveRight(speed);
	}
	
	/**
	 * Drive the left wheels
	 * @param speed
	 */
	public void driveLeft(float speed) {}		//TODO
	
	
	/**
	 * Drive right wheels
	 * @param speed
	 */
	public void driveRight(float speed) {}		//TODO
	
	
}
