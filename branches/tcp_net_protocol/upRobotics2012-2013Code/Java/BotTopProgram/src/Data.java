

/**
 * 
 * ArduinoInput
 * 
 * Data structure / thread for capturing and storing data from 
 * the arduino.
 * 
 * @author Matt Delaney, Matt Holland
 *
 */
public class Data  {

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


	public void setIrFront(float irFront) {
		synchronized (this) {
			this.irFront = irFront;
		}
	}

	public void setIrBack(float irBack) {
		synchronized (this) {
			this.irBack = irBack;
		}
	}

	public void setIrLeft(float irLeft) {
		synchronized (this) {
			this.irLeft = irLeft;
		}
	}

	public void setIrRight(float irRight) {
		synchronized (this) {
			this.irRight = irRight;
		}
	}

	public void setPotBucket(float potBucket) {
		synchronized (this) {
			this.potBucket = potBucket;
		}
	}

	public void setPotArm(float potArm) {
		synchronized (this) {
			this.potArm = potArm;
		}
	}

	public void setGyroYaw(float gyroYaw) {
		synchronized (this) {
			this.gyroYaw = gyroYaw;
		}
	}

	public void setGyroPitch(float gyroPitch) {
		synchronized (this) {
			this.gyroPitch = gyroPitch;
		}
	}

	public void seteStop(boolean eStop) {
		synchronized (this) {
			this.eStop = eStop;
		}
	}

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

}
