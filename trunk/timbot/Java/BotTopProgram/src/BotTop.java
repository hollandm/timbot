/**
 * BotTop
 * 
 * Controller thread on the robot.
 * 
 * @Author Matt Delaney
 */
public class BotTop {

	ArduinoReader arduinoReader;
	ArduinoWriter arduinoController;
	AnimaticsController motorController;
	
	AI ai;
	NetworkComms net;
	
	Data data;
	
	
	public int mode = 0;
	
	public static final int MODE_PREPARATION = 0;
	public static final int MODE_AUTONOMOUS = 1;
	public static final int MODE_MANUAL = 2;
	public static final int MODE_STOP = -1;
	
	public BotTop() {
		
		data = new Data();
		arduinoReader = new ArduinoReader();
		
		motorController = new AnimaticsController();
		arduinoController = new ArduinoWriter();
		
		net = new NetworkComms(this);
		ai = new AI(this,data);	
		
	}
	
	/**
	 * Command called when EStop triggered over network or Arduino
	 * Tells everything to stop then shuts down computer
	 */
	public void EStop() {
		
	}
	
	/**
	 * Sends an SMI command to the motors
	 * Must be in proper format
	 */
	public void sendMotorCommand() {
		
	}
	
	/**
	 * Actuate arm to given distance
	 */
	public void actuateArm(double dist) {
		
	}
	
	/**
	 * Actuate bucket to given distance
	 */
	public void actuateBucket(double dist) {
		
	}
	
	
	/**
	 * start are program
	 */
	public static void main(String args[]) {
		
		BotTop control = new BotTop();
		
		
	}

	
	
}
