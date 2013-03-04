

/**
 * AI
 * 
 * The AI thread. Controls the robot when it's in autonomous mode.
 * @author Matt
 *
 */

public class AI implements Runnable {

	private int aiState = 0;


	int startPosition = -1; // Start Position. ID's corner by definition (1-4).
	int startAngle = -1; // starting rotation / angle.
	
	
	public static final int STATE_MANUAL_CONTROL = -1;
	public static final int STATE_WAITING_FOR_START_COMMAND = 0;
	public static final int STATE_FIND_STARTING_ORIENTATION = 1;
	public static final int STATE_GO_TO_DIG_ZONE = 2;
	public static final int STATE_DIG = 3;
	public static final int STATE_TRAVEL_TO_DUMP_ZONE = 4;
	public static final int STATE_TRAVEL_BACK_TO_DIG_ZONE = 5; // loop back to: 3
	public static final int STATE_REQUEST_MANUAL_CONTROL = 99; // may not use this. 

	@Override
	public void run() {
		switch (aiState){
		case -1: // Manual Control: Do nothing! Should be shut off by BotTop instead.
		case 0: // waiting for start command. Still do nothing!
			Thread.yield();
			break;
		case 1:
			figureOutWhereWeAreStarting();
			break;
		case 2:
			goToDigAreaForTheFirstTime();
			break;
		case 3:
			collectDust();
			break;
		case 4:
			goAndDumpDust();
			break;
		case 5:
			returnToDigZone();
			break;
		case 99:
			break;
		}
		
		
	}
	
	/**
	 * figure out where you are.
	 */
	private void figureOutWhereWeAreStarting() {
		// TODO Auto-generated method stub
		
	}

	/**
	 * go to the dig area for the first time.
	 */
	private void goToDigAreaForTheFirstTime() {
		// TODO Auto-generated method stub
		
	}
	
	/**
	 * Dig dust; raise bucket for travel
	 */
	private void collectDust() {
		// TODO Auto-generated method stub
		
	}
	
	/**
	 * Travel to dump zone and dump
	 */
	private void goAndDumpDust() {
		// TODO Auto-generated method stub
		
	}
	/**
	 * Return to the dig zone!
	 */
	private void returnToDigZone() {
		// TODO Auto-generated method stub
		
	}
	
	
	
	public void changeState(int newState) {
		
		aiState = newState;
		System.out.println("AI State changed to: " + aiState);
		
	}
	
	
	/**
	 * Constructor. Requires an input-data pointer.
	 * TODO: Does this need an output reference?
	 * @param data (sensor data from Arduino)
	 * @param out (how to talk to the arduino to actually do stuff)
	 */
	public AI(BotTop robot, Data data) {
		//TODO
	}
	
	/**
	 * getAIState()
	 * @return AI's current state
	 */
	public int getAiState() {return aiState;}
	

	
}
