
public class AI implements Runnable {

	int aiState = 0;
	
	
	private static final int STATE_MANUAL_CONTROL = -1;
	private static final int STATE_WAITING_FOR_START_COMMAND = 0;
	private static final int STATE_FIND_STARTING_ORIENTATION = 1;
	private static final int STATE_GO_TO_DIG_ZONE = 2;
	private static final int STATE_DIG = 3;
	private static final int STATE_TRAVEL_TO_DUMP_ZONE = 4;
	private static final int STATE_TRAVEL_BACK_TO_DIG_ZONE = 5; // loop back to: 3
	private static final int STATE_REQUEST_MANUAL_CONTROL = 99;

	@Override
	public void run() {
		
		
		
	}
	
	public void changeState(int newState) {
		
		aiState = newState;
		System.out.println("AI State changed to: " + aiState);
		
	}
	
	
}
