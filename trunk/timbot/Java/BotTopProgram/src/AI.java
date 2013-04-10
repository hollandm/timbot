

/**
 * AI
 * 
 * The AI thread. Controls the robot when it's in autonomous mode.
 * @author Matt
 *
 */

public class AI implements Runnable {

	private int aiState = 0;
	private boolean isManualControl = false;

	int startPosition = -1; // Start Position. ID's corner by definition (1-4).
	int startAngle = -1; // starting rotation / angle.
	
	
	//public static final int STATE_MANUAL_CONTROL = -1;
	public static final int STATE_WAITING_FOR_START_COMMAND = 0;
	public static final int STATE_FIND_STARTING_ORIENTATION = 1;
	public static final int STATE_GO_TO_DIG_ZONE = 2;
	public static final int STATE_DIG = 3;
	public static final int STATE_TRAVEL_TO_DUMP_ZONE = 4;
	public static final int STATE_TRAVEL_BACK_TO_DIG_ZONE = 5; // loop back to: 3
	public static final int STATE_REQUEST_MANUAL_CONTROL = 99; // may not use this. 

	@Override
	public void run() {
		// print timestamp
		
		// if we're not in manual-mode or waiting-mode, run the loop.
	if((isManualControl || aiState == STATE_WAITING_FOR_START_COMMAND) ){
		Thread.yield();
	}else{
		switch (aiState){
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
		
	}
	
	/**
	 * figure out where you are.
	 */
	private void figureOutWhereWeAreStarting() {
		// TODO: Capture images and use sensor data to figure out where we are.
		
		// Set whatever variables state 2 needs to drive.
		
		// Proceed to next state.
		this.aiState = STATE_GO_TO_DIG_ZONE;
	}

	/**
	 * go to the dig area for the first time.
	 */
	private void goToDigAreaForTheFirstTime() {
		// TODO Auto-generated method stub
		
		// Using sensor data from part 1 (and ongoing sensor data, if desired), drive to the dig area.
		
		// Keep the beacons on top of each other.
		// don't forget to drive 'backwards'!
		
		// lower bucket as we go[?]
		
		// Once we have arrived, proceed to next state.
		this.aiState = STATE_DIG;
	}
	
	/**
	 * Dig dust; raise bucket for travel
	 */
	private void collectDust() {
		// TODO Auto-generated method stub
		
		// Dig. Figure this out once we have a working robot.
		
		
		// Once we've collected dust and raised the bucket, proceed to the next state.
		this.aiState = STATE_TRAVEL_TO_DUMP_ZONE;
	}
	
	/**
	 * Travel to dump zone and dump
	 */
	private void goAndDumpDust() {
		// TODO Auto-generated method stub
		
		// determine where we need to drive to
		
		// drive there
		
		// dump dust.
		
		// raise the bucket
		
		// Proceed to next state.
		this.aiState = STATE_TRAVEL_BACK_TO_DIG_ZONE;
		
	}
	/**
	 * Return to the dig zone!
	 */
	private void returnToDigZone() {
		// TODO Auto-generated method stub
		// drive backwards to the dig zone
		
		// use IR sensor to determine when we're in the right range
		
		// loop back to dig state
		this.aiState = STATE_DIG;
	}
	
	
	
	public void changeState(int newState) {
		
		aiState = newState;
		System.out.println("AI State changed to: " + aiState);
		
	}
	
	
	/**
	 * Constructor. Requires an input-data pointer.
	 * TODO: Does this need an output reference?
	 * 'out' is BOTTOP
	 * 
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

	/**
	 * startRun()
	 * 
	 * called by BotTop to start the robot on its run once we get the go-ahead.
	 */
	public void startRun(){
		if(this.aiState == STATE_WAITING_FOR_START_COMMAND){
			this.aiState = STATE_FIND_STARTING_ORIENTATION;
		}
	}
	
	/**
	 * setManualControl()
	 * 
	 * sets the manual-control switch.
	 * 
	 * @param isManualControl set manual control to true or false
	 */
	
	public void setManualControl(boolean manControl){
		//TODO: for competition, make one-way (only set if true).
		this.isManualControl = manControl;
	}
	

	
}
