/**
 * BotTop
 * 
 * Controller thread on the robot.
 * 
 * @Author Matt Delaney
 */
public class BotTop {

	AI ai;
	AInputData data;
	AOutput out;
	NetworkComms net;
	
	public int mode = 0;
	
	public static final int MODE_PREPARATION = 0;
	public static final int MODE_AUTONOMOUS = 1;
	public static final int MODE_MANUAL = 2;
	public static final int MODE_STOP = -1;
	
	public static void main(String args[]) {
		
		BotTop control = new BotTop();
		
		
	}

	
	
}
