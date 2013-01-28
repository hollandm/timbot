

/**
 * 
 * AInputData
 * 
 * Data structure / thread for capturing and storing data from 
 * the arduino.
 * 
 * @author Matt Delaney, Matt Holland
 *
 */
public class AInputData implements Runnable {
	
	// IR values are in CENTIMETERS.
	// Accurate from 30cm to 150cm.
	private float irFront = 0;
	private float irBack = 0;
	private float irLeft = 0;
	private float irRight = 0;
	
	private float potBucket = 0;
	private float potArm = 0;
	
	private float gyroYaw = 0;
	private float gyroPitch = 0;
	
	//TODO: Gyro values might be more useful in another unit?
	
	private boolean eStop = false;
	
	
	/* Raw Sensor Input Values */
	private float m_irFrontRaw = 0;
	private float m_irBackRaw = 0;
	private float m_irLeftRaw = 0;
	private float m_irRightRaw = 0;
	
	private float m_potBucketRaw = 0;
	private float m_potArmRaw = 0;
	
	private float m_gyroYawRaw = 0;
	private float m_gyroPitchRaw = 0;
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
	 * gets the value of gyroPitch
	 * @return
	 */
	public float getGyroPitch() {
		synchronized (this) {
			return gyroPitch;
		}
	}
	
	/**
	 * reads data from the arduino
	 */
	public void getData() {
		// TODO: GET DATA. Store to m_*Raw variables.
		
		
		convertData();
	}


	/**
	 * converts raw data into usable information.
	 */
private void convertData() {
		synchronized(this){
			// convert IR sensor data to Centimeters:
			irLeft = (400 / m_irLeftRaw *33);
			irRight = (400 / m_irRightRaw *33);
			irFront = (400 / m_irFrontRaw *33);
			irBack = (400 / m_irBackRaw *33);
			
			// TODO convert Gyro values to usable data
			
			// TODO convert bucketRaw and potArmRaw to usable data (cm)
			
		}//synchronized
		
	}

	@Override
	public void run() {
		synchronized (this) {
			getData();
		}
		Thread.yield();
		
	}
	
}
