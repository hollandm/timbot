

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
public class ArduinoReader implements Runnable {
	
	/* Data storage module */
	Data myData;
	
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
	 * reads data from the arduino
	 */
	public void getData() {
		// TODO: GET DATA. Store to m_*Raw variables.
		
		
		convertData();

		myData.setIrFront(m_irFrontRaw);
		myData.setIrBack(m_irBackRaw);
		myData.setIrLeft(m_irLeftRaw);
		myData.setIrRight(m_irRightRaw);
		
	}


	/**
	 * converts raw data into usable information.
	 */
private void convertData() {
		synchronized(this){
			// convert IR sensor data to Centimeters:
			m_irLeftRaw = (400 / m_irLeftRaw *33);
			m_irRightRaw = (400 / m_irRightRaw *33);
			m_irFrontRaw = (400 / m_irFrontRaw *33);
			m_irBackRaw = (400 / m_irBackRaw *33);
			
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
