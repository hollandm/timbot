
public class AI implements Runnable {

	int aiState = 0;

	@Override
	public void run() {
		
		
		
	}
	
	public void changeState(int newState) {
		
		aiState = newState;
		System.out.println("AI State changed to: " + aiState);
		
	}
	
	
}
