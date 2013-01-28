
public class AInputData implements Runnable {
	
	private float irFront = 0;
	private float irBack = 0;
	private float irLeft = 0;
	private float irRight = 0;
	
	private float potBucket = 0;
	private float potArm = 0;
	
	private float gyroYaw = 0;
	
	private boolean eStop = false;
	
	/**
	 * gets the value of front ir sensor
	 * @return
	 */
	public synchronized float getIrFront() {
		synchronized (this) {
			return irFront;	
		}
	}
	
	/**
	 * gets the value of back ir sensor
	 * @return
	 */
	public float getIrBack() {
		synchronized (this) {
			return irBack;
		}
	}
	
	/**
	 * gets the value of left ir sensor
	 * @return
	 */
	public float getIrLeft() {
		synchronized (this) {
			return irLeft;
		}
	}
	
	/**
	 * gets the value of right ir sensor
	 * @return
	 */
	public float getIrRight() {
		synchronized (this) {
			return irRight;
		}
	}
	
	/**
	 * gets the value of potentiometer bucket
	 * @return
	 */
	public float getPotBucket() {
		synchronized (this) {
			return potBucket;
		}
	}
	
	/**
	 * gets the value of potentiometer arm
	 * @return
	 */
	public float getPotArm() {
		synchronized (this) {
			return potArm;
		}
	}
	
	/**
	 * gets the value of gyroYaw
	 * @return
	 */
	public float getGyroYaw() {
		synchronized (this) {
			return gyroYaw;
		}
	}
	
	/**
	 * reads data from the arduino
	 */
	public void getData() {}


	@Override
	public void run() {
		synchronized (this) {
			getData();
		}
		Thread.yield();
		
	}
	
}
